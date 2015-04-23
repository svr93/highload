#!/bin/bash
for i in {1..50}
do
  echo 'nginx_'
  ab -n 50000 -c 100 \
  -r http://localhost/ | grep "Requests per second" | tee -a t50000.txt
  echo '================='
  
  echo 'SVR_'
  ab -n 50000 -c 100 \
  -r http://localhost:8000/httptest/wikipedia_russia.html | \
  grep "Requests per second" | tee -a t50000.txt
  echo '================='
  
done
