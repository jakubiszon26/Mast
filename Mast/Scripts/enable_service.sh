#!/bin/bash
#get a service name to stop;
name=$(cat "/run/Mast/service_name")
systemctl enable $name >> /run/Mast/logs
echo "siema" >> /home/jakub/plik
