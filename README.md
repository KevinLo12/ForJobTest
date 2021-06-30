OS:Ubuntu14.04  
g++:4.9.4

[how to get sourcecode]  
git clone https://github.com/KevinLo12/ForJobTest.git

[pre-install]  
sudo apt-get install tcpdump  
sudo apt-get install tshark  
sudo apt-get install libpcap-dev  

[how to build]  
cd ForJobTest  
#build wrapped_tcpdump_for_tcp_sniffer tool  
make wrapped_tcpdump_for_tcp_sniffer  
#build wrapped_tshark_for_tcp_sniffer tool  
make wrapped_tshark_for_tcp_sniffer  
#build libpcap_for_tcp_sniffer tool  
make libpcap_for_tcp_sniffer  

[how to use]  
cd ForJobTest  
#for wrapped_tcpdump_for_tcp_sniffer tool  
sudo ./tcp_sniffer -i eth0 -f /var/log/tcp_sniffing_log  
cat /var/log/tcp_sniffing_log  

#for wrapped_tshark_for_tcp_sniffer tool  
./tcp_sniffer -i eth0 -f /var/log/tcp_sniffing_log  
cat /var/log/tcp_sniffing_log  

#for libpcap_for_tcp_sniffer tool  
sudo ./tcp_sniffer -i eth0 -f /var/log/tcp_sniffing_log  
cat /var/log/tcp_sniffing_log  

[how to do Auto testing]  
cd ForJobTest  
./test_tcp_sniffer.sh  
select tcp_sniffer tool item  
1:wrapped_tcpdump_for_tcp_sniffer  
2:wrapped_tshark_for_tcp_sniffer  
3:libpcap_for_tcp_sniffer  
