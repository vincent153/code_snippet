string getIP(string iface_name="eth0")
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);
    string ret = "";
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            cout<<string(ifa->ifa_name)<<":"<<addressBuffer<<endl;
            if(string(ifa->ifa_name)==iface_name)
            {
                ret = string(addressBuffer);
                break;
            }
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);    
    cout<<"read ip:"<<ret<<endl;
    return ret;
}


bool netwrokAvail()
{
    FILE *output;
    if(!(output = popen("/sbin/route -n | grep -c '^0\\.0\\.0\\.0'","r"))){
        return 1;
    }
    unsigned int i;
    fscanf(output,"%u",&i);
    if(i==0)
    {
        cerr<<"There is no internet connection\n";
    }           
    else if(i==1)
    {
        cerr<<"There is internet connection\n";
    }
    pclose(output);
    return i;
}
