#!/bin/bash
COLOR_REST='\e[0m';
COLOR_RED='\e[0;31m';
COLOR_GREEN='\e[0;32m';
COLOR_YELLOW='\e[0;33m';


echo "select tcp_sniffer tool"
echo "1:wrapped_tcpdump_for_tcp_sniffer"
echo "2:wrapped_tshark_for_tcp_sniffer"
echo "3:libpcap_for_tcp_sniffer"
read -p "" number
echo "your tool is ${number}"

if [ "$number" == "2" ]; then
	echo "[Permission] sudo Permission test"
    sudoTest=`sudo ./tcp_sniffer -i eth0 -f tcp_sniffer.txt 2>&1`
    #echo $sudoTest 

    testResult=`echo $sudoTest | grep "root"`
    #echo $testResult 

    if [ "$testResult" == "" ]; then
	    echo -e "[Permission] ${COLOR_RED} Fail ${COLOR_REST}"
            result="[Permission] ${COLOR_RED} Fail ${COLOR_REST}"
    else
	    echo -e "[Permission] ${COLOR_GREEN} Pass ${COLOR_REST}"
            result="[Permission] ${COLOR_GREEN} Pass ${COLOR_REST}"
    fi
else
	echo "[Permission] no sudo Permission test"
    sudoTest=`./tcp_sniffer -i eth0 -f tcp_sniffer.txt`
    #echo $sudoTest 

    testResult=`echo $sudoTest | grep "You don't have permission"`
    #echo $testResult 

    if [ "$testResult" == "" ]; then
	    echo -e "[Permission] ${COLOR_RED} Fail ${COLOR_REST}"
            result="[Permission] ${COLOR_RED} Fail ${COLOR_REST}"
    else
	    echo -e "[Permission] ${COLOR_GREEN} Pass ${COLOR_REST}"
            result="[Permission] ${COLOR_GREEN} Pass ${COLOR_REST}"
    fi
fi

echo "[Device] wrong interface name test"
Test=`sudo ./tcp_sniffer -i kkk -f tcp_sniffer.txt`
#echo $Test 

testResult=`echo $Test | grep "No such device exists"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[Device] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[Device] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[Device] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[Device] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo "[OutputFile] wrong outputfile name test"
Test=`sudo ./tcp_sniffer -i eth0 -f C:/tcp_sniffer.txt`
#echo $Test 

testResult=`echo $Test | grep "No such file or directory"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[OutputFile] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[OutputFile] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[OutputFile] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[OutputFile] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo "[Parameter-1] wrong parameter test"
Test=`sudo ./tcp_sniffer -i eth0 -f C:/tcp_sniffer.txt -p 2>&1`
#echo $Test 

testResult=`echo $Test | grep "Usage:"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[Parameter-1] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[Parameter-1] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[Parameter-1] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[Parameter-1] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo "[Parameter-2] wrong parameter test"
Test=`sudo ./tcp_sniffer -i eth0 2>&1`
#echo $Test 

testResult=`echo $Test | grep "Usage:"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[Parameter-2] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[Parameter-2] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[Parameter-2] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[Parameter-2] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo "[Parameter-3] wrong parameter test"
Test=`sudo ./tcp_sniffer -i eth0 eth1 -f C:/tcp_sniffer.txt 2>&1`
#echo $Test 

testResult=`echo $Test | grep "Usage:"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[Parameter-3] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[Parameter-3] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[Parameter-3] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[Parameter-3] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo "[Parameter-4] wrong parameter test"
Test=`sudo ./tcp_sniffer ddd -i eth0 -f tcp_sniffer.txt 2>&1`
#echo $Test 

testResult=`echo $Test | grep "Usage:"`
#echo $testResult 

if [ "$testResult" == "" ]; then
	echo -e "[Parameter-4] ${COLOR_RED} Fail ${COLOR_REST}"
        result="${result}\n[Parameter-4] ${COLOR_RED} Fail ${COLOR_REST}"
else
	echo -e "[Parameter-4] ${COLOR_GREEN} Pass ${COLOR_REST}"
        result="${result}\n[Parameter-4] ${COLOR_GREEN} Pass ${COLOR_REST}"
fi

echo -e "\n\n---- Auto Test Result ----"
echo -e $result
