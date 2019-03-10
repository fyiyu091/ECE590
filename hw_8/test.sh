#!/bin/bash

OUT="log.txt"  # log for server
MAKE="Makefile" 

docker container stop $(docker container ls -aq)
docker system prune

# create two container for server and client and run them in detach mode
SERVER_ID="$(docker run --name ECEP590-server -v $PWD:/source -di klavins/ecep520:cppenv-http)"
CLIENT_ID="$(docker run --name client --link ECEP590-server -v $PWD:/source -di klavins/ecep520:cppenv-http)"

echo "Start compilation..."
#docker exec $SERVER_ID make -f $MAKE spotless #>> $OUT
#docker exec $SERVER_ID make -f $MAKE #>> $OUT

printf "\n=====  Test Problem 1  =====\n"
printf "Run temperature server...\n"
docker exec $SERVER_ID ./test/bin/temperature_server > $OUT & #sleep 2 ; kill $!
server_pid=$!
printf "Run unit test in client container...\n"
docker exec $CLIENT_ID ./test/bin/p1_test #>> $OUT &
kill $server_pid
printf "Force removing container $SERVER_ID\n"
docker rm --force $SERVER_ID
printf "Force removing container $CLIENT_ID\n"
docker rm --force $CLIENT_ID

# restart server and client because we want data in server is cleaned to test next problem
# based on current code base, we have no choice to restart the server... 
printf "\n=====  Test Problem 2  =====\n"
SERVER_ID="$(docker run --name ECEP590-server -v $PWD:/source -di klavins/ecep520:cppenv-http)"
CLIENT_ID="$(docker run --name client --link ECEP590-server -v $PWD:/source -di klavins/ecep520:cppenv-http)"

printf "Run temperature server...\n"
docker exec $SERVER_ID ./test/bin/temperature_server >> $OUT & #sleep 2 ; kill $!
server_pid=$!
printf "Run unit test in client container...\n"
docker exec $CLIENT_ID ./test/bin/p2_test #>> $OUT &
kill $server_pid

printf "\n=====  End test  =====\n"
# stop all running container
docker container stop $(docker container ls -aq)
# remove server and client containers
printf "Force removing container $SERVER_ID\n"
docker rm --force $SERVER_ID
printf "Force removing container $CLIENT_ID\n"
docker rm --force $CLIENT_ID
