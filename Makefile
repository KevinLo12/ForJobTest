EXE :=tcp_sniffer
CC:=g++
CFLAGS = -g -Wall -ansi

wrapped_tcpdump_for_tcp_sniffer:
	$(CC) $(CFLAGS) -o $(EXE) wrapped_tcpdump_for_tcp_sniffer.cpp
wrapped_tshark_for_tcp_sniffer:
	$(CC) $(CFLAGS) -o $(EXE) wrapped_tshark_for_tcp_sniffer.cpp
libpcap_for_tcp_sniffer:
	$(CC) $(CFLAGS) -o $(EXE) libpcap_for_tcp_sniffer.cpp -lpcap
#socket_for_tcp_sniffer:
	#$(CC) $(CFLAGS) -o $(EXE) socket_for_tcp_sniffer.cpp

strategy_dp_tcp_sniffer:
	$(CC) $(CFLAGS) -o $(EXE) main.cpp WrappedTcpdump.cpp WrappedTshark.cpp WrappedLibpcap.cpp -lpcap

.PHONY:clean
clean:
	rm -rf $(EXE)
