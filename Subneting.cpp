#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int stringToInt(const string &str)
{
    // #include <cmath>
    // This function convert string to integer.
    int integer=0;
    int mult = pow(10,str.length()-1);
    for (char i : str)
    {
        integer += (i-48)*mult;
        mult/=10;
    }
    return integer;
}

class IP
{
private:
    int ctr=0;
public:
    // some member variables
    int first , second, third, fourth;
    char Class;

    // some constructors
    IP():first(0), second(0), third(0), fourth(0), Class(' '){ }
    IP(string ip)
    {
        auto* arr= new string [4];
        for (int i = 0; i < ip.length(); ++i)
        {
            if(ip[i]=='.') {
                ctr++;
                i++;
            }
            arr[ctr]+=ip[i];

            first= stringToInt(arr[0]);
            second= stringToInt(arr[1]);
            third= stringToInt(arr[2]);
            fourth= stringToInt(arr[3]);
            Class = findClass();

        }
        ctr=0;
        delete[] arr;
    }
    IP(int fi, int se=0, int th=0, int fo=0, char cls=' '):first(fi), second(se), third(th), fourth(fo),Class(cls){ }
    IP(const IP& ip):first(ip.first), second(ip.second), third(ip.third), fourth(ip.fourth), Class(ip.Class){ }

    // some modifiers
    void reset(int lastOctets=0)
    {
        // this function resets the last given octets
        if(lastOctets == 0 || lastOctets == 4){
            first = 0;
            second = 0;
            third = 0;
            fourth = 0;
        }
        else if(lastOctets == 1 ) { fourth = 0; }
        else if(lastOctets == 2 ) { third = 0;fourth = 0; }
        else if(lastOctets == 3 ) { second = 0;third = 0; fourth = 0; }

    }

    // some getters
    char findClass() const
    {
        // this function returns the class of the ip X-OR (!) if it is not valid ip
        if(first >= 0 && first <= 127)
            return 'A';
        if(first >= 128 && first <= 191)
            return 'B';
        if(first >= 129 && first <= 223)
            return 'C';
        if(first >= 224 && first <= 239)
            return 'D';
        if(first >= 240 && first <= 255)
            return 'E';

        return '!';
    }
    void print() const{ cout << first <<'.'<< second <<'.'<< third <<'.'<< fourth;}
    string stringIp ()const
    {
        // this function returns the ip as a string
        string strIp= to_string(first)+'.'+to_string(second)+'.'+to_string(third)+'.'+to_string(fourth);
        return strIp;
    }
    bool isvalid()const
    {
        // this function returns true if thr ip is valid and false if it's not.
        if(first>=0 && first<=255 && second>=0 && second<=255 && third>=0 && third<=255 && fourth>=0 && fourth<=255)
            return true;
        return false;
    }

};


void interface(string& row_ip, char& way, int& num)
{
    /*
     * This is the interface of the program.
     * It asks the user to enter any of the hosts/net or the subnets or number of 1s in netmask.
     * It takes data from the user and initialize the variables[row_ip,way,num]
     * It also checks if the ip is valid or not.
     */

    cout << " Enter Your IP Address Sir>>";getline(cin, row_ip);
    IP temp_ip = row_ip;

    if(temp_ip.isvalid())
    {
        cout << " Enter [h] To Enter The Number Of Hosts.\n" <<
             " Enter [n] To Enter The Number Of Subnets.\n" <<
             " Enter [b] To Enter The Number Of bits(1s).\n";
        cout << ">>";
        cin >> way;

        if (way == 'h') {
            cout << " Enter The Number Of Hosts>>";
            cin >> num;
        } // num of desired hosts not including the NetID nor Casting
        else if (way == 'n') {
            cout << " Enter The Number Of Subnets>>";
            cin >> num;
        }
        else if (way == 'b') {
            cout << " Enter The Number Of bits>>";
            cin >> num;
        } // total number of bits(1s)
        else cout << "Invalid Entry!";
    }
    else
        cout << "Invalid ip address";
}
// checkNumC: returns the total number of IPs including (broadcast, Subnet ID) and 0 if it's not valid number.
int checkNumC(int num)
{
    // returns the total number of IPs including (broadcast, Subnet ID) and 0 if it's not valid number.
    int arr[9]={1,2,4,8,16,32,64,128,256};
    for (int i = 0; i < 9; i++) {
        if(arr[i]==num+2)
            return num+2;
        if((num+2)>arr[i] && (num+2)<arr[i+1])
            return arr[i+1];
    }
    return 0;
}
// checkNumB: returns the total number of IPs including (broadcast, Subnet ID) and 0 if it's not valid number.
int checkNumB(int num)
{

    int arr[17]={1,2,4,8,16,32,64,128,256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
    for (int i = 0; i < 17; i++) {
        if(arr[i]==num+2)
            return num+2;
        if((num+2)>arr[i] && (num+2)<arr[i+1])
            return arr[i+1];
    }
    return 0;
}
// checkNumA: returns the total number of IPs including (broadcast, Subnet ID) and 0 if it's not valid number.
int checkNumA(int num)
{

    int arr[25]={1,2,4,8,16,32,64,128,256, 512,
                 1024, 2048, 4096, 8192, 16384, 32768, 65536,
                 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,16777216};
    for (int i = 0; i < 25; i++) {
        if(arr[i]==num+2)
            return num+2;
        if((num+2)>arr[i] && (num+2)<arr[i+1])
            return arr[i+1];
    }
    return 0;
}



void print(const IP netIDs[], const IP firstUsables[], const IP lastUsables[], const IP bradCasts[], int subnets, int bits, int hosts, int hops, const IP& mask)
{
    cout << "\nCLASS: "<< netIDs[0].findClass() << endl;
    cout << "\nHosts/Net:" << hosts  << "   Total Hosts:"<< hosts*subnets <<  "   hops:"<< hops << "   subnets:" << subnets << "   bits:" << bits << "   mask:"<< mask.stringIp()<< endl<<endl;
    for (int i = 0; i < subnets; ++i) {
        cout << "Subnet "            << "[" << i+1 << "]\n ";
        cout << " NetId= "           << netIDs[i].stringIp()<<"/"<<bits;
        cout << "    Usable start= " << firstUsables[i].stringIp()
             << "    Usable End= "   << lastUsables[i].stringIp()
             << "    Broadcast= "    << bradCasts[i].stringIp()<< endl<< endl;
    }
}

void classC(const IP& ip,char way,int num)
{

    IP firstIp(ip);firstIp.fourth=0;
    string strIp=firstIp.stringIp(); strIp.pop_back();

    string mask="255.255.255.";
    int hosts=0, subnets=0, bits=0, hops=0;  //  (bits) is the total number of 1s in the new subnet mask = 24+way of 1s from the host octet
    if(way == 'h')
    {
        hosts=num;
        hosts= checkNumC(hosts) - 2; // total number of usable IPs
        hops = checkNumC(hosts);  // total number of IPs including (broadcast, Subnet ID)
        bits = 24 + (8- log2(hops));
        subnets = pow(2,bits-24);

    } else if (way == 'n')
    {
        subnets=num;
        subnets= checkNumC(subnets - 2); // total number of subnets
        bits= 24 + log2(subnets);
        hops = pow(2,8-(bits-24));
        hosts = hops-2;

    } else if(way == 'b')
    {
        bits=num;
        if(bits <24 || bits > 32)
            cout << " invalid number of bits";
        hops = pow(2,8-(bits-24));
        hosts = hops-2;
        subnets = pow(2,bits-24);
    }

    mask+= to_string(256-hops);

    // printing
    if(way=='h' || way=='n' || way=='b' ) {
        cout << "\nClass C\nHosts/Net:" << hosts << "   Total Hosts " << hosts * subnets << "   hops:" << hops
             << "   subnets:" << subnets << "   bits:" << bits << "   mask:" << mask << endl << endl;
        for (int i = 0; i < subnets; ++i) {

            cout << "Subnet " << "[" << i + 1 << "]\n ";
            cout << " NetId= " << strIp << to_string(hops * i) << "/" << bits
                 << "    Usable start= " << strIp << to_string(hops * i + 1)
                 << "    Usable End= " << strIp << to_string(hops * i + hops - 2)
                 << "    Broadcast= " << strIp << to_string(hops * i + hops - 1) << endl << endl;

        }
    }

}
void classB(const IP& ip,char way,int num)
{
    IP netID=ip;
    netID.reset(2);
    IP mask("255.255.0.0");
    int hosts=0, subnets=0, bits=0, hops=0;  //  (bits) is the total number of 1s in the new subnet mask = 16+num of 1s from the host octets

    if(way == 'h')
    {
        hosts=num;
        hosts= checkNumB(hosts) - 2; // total number of usable IPs
        hops = checkNumB(hosts);  // total number of IPs including (broadcast, Subnet ID)
        bits = 16 + (16- log2(hops));
        subnets = pow(2,bits-16);

    } else if (way == 'n')
    {
        subnets=num;
        subnets= checkNumB(subnets - 2); // total number of subnets
        bits= 16 + log2(subnets);
        hops = pow(2,16-(bits-16));
        hosts = hops-2;

    } else if(way == 'b')
    {
        bits=num;
        if(bits <16 || bits > 32)
            cout << " invalid number of bits";
        else {
            hops = pow(2, 16 - (bits - 16));
            hosts = hops - 2;
            subnets = pow(2, bits - 16);
        }
    }

    // setting the new subnet mask
   if(hosts<=256)
   {
       mask.third=255;
       mask.fourth=256-hops;
   } else
   {
       mask.fourth=0;
       mask.third =256-(hops/256);
   }


    IP* netIDs       = new IP[subnets];
    IP* firstUsables = new IP[subnets];
    IP* lastUsables  = new IP[subnets];
    IP* bradCasts    = new IP[subnets];
    for (int i = 0; i < subnets; ++i)
    {
        netIDs[i].first=netID.first;
        netIDs[i].second=netID.second;

        if(hosts<=256)
        {
            if(i!=0)
            {
                netIDs[i].fourth = netIDs[i - 1].fourth + hops;
                netIDs[i].third  = netIDs[i - 1].third ;
            }
            if(netIDs[i].fourth == 256)
            {
                netIDs[i].fourth = 0;
                netIDs[i].third += 1;
            }

            firstUsables[i] = netIDs[i] ;lastUsables[i] =netIDs[i]; bradCasts[i] = netIDs[i];

            firstUsables[i].fourth = netIDs[i].fourth+1;
            lastUsables[i].fourth  = netIDs[i].fourth+hosts;
            bradCasts[i].fourth    = netIDs[i].fourth+hosts + 1;

        } else
        {
            if(i!=0)
            {
                netIDs[i].third = netIDs[i - 1].third + hops/256;
            }

            firstUsables[i] = netIDs[i] ;lastUsables[i] =netIDs[i]; bradCasts[i] = netIDs[i];

            firstUsables[i].fourth +=1;
            lastUsables[i].third   += (hops)/256-1;
            lastUsables[i].fourth   = 254;
            bradCasts[i].third      = lastUsables[i].third;
            bradCasts[i].fourth     = 255;

        }


    }

    if(way=='h' || way=='n' || way=='b' )
        print(netIDs, firstUsables,  lastUsables,  bradCasts,  subnets,  bits,  hosts,  hops,  mask);

    delete[] netIDs;
    delete[] firstUsables;
    delete[] lastUsables;
    delete[] bradCasts;
}
void classA(const IP& ip,char way,int num)
{
    IP netID=ip;
    netID.reset(3);
    IP mask("255.0.0.0");
    int hosts=0, bits=0, hops=0;  //  (bits) is the total number of 1s in the new subnet mask = 16+num of 1s from the host octets
    long long subnets=0.0;
    if(way == 'h')
    {
        hosts=num;
        hosts= checkNumA(hosts) - 2; // total number of usable IPs
        hops = checkNumA(hosts);  // total number of IPs including (broadcast, Subnet ID)
        bits = 8 + (24- log2(hops));
        subnets = pow(2,bits-8);

    } else if (way == 'n')
    {
        subnets=num;
        subnets= checkNumA(subnets - 2); // total number of subnets
        bits= 8 + log2(subnets);
        hops = pow(2,24-(bits-8));
        hosts = hops-2;

    } else if(way == 'b')
    {
        bits=num;
        if(bits <8 || bits > 32)
            cout << " invalid number of bits";
        else {
            hops = pow(2, 24 - (bits - 8));
            hosts = hops - 2;
            subnets = pow(2, bits - 8);
        }
    }

    // setting the new subnet mask
    if(hosts<=256)
    {
        mask.second=255;
        mask.third=255;
        mask.fourth=256-hops;
    } else if (hosts>256 && hosts<= (256*256))
    {
        mask.second=255;
        mask.third =256-(hops/256);
        mask.fourth=0;
    }
    else if(hosts>(256*256))
    {
        mask.second=256-(hops/(256*256));
        mask.third =0;
        mask.fourth=0;
    }

    // generating the net-id, usable start , end and broadcast
    IP* netIDs       = new IP[subnets];
    IP* firstUsables = new IP[subnets];
    IP* lastUsables  = new IP[subnets];
    IP* bradCasts    = new IP[subnets];
    for (int i = 0; i < subnets; ++i)
    {
        netIDs[i].first=netID.first;

        if(hosts<=256)
        {
            if(i!=0)
            {
                netIDs[i].fourth = netIDs[i - 1].fourth + hops;
                netIDs[i].third  = netIDs[i - 1].third ;
                netIDs[i].second = netIDs[i - 1].second ;
            }
            if(netIDs[i].fourth == 256)
            {
                netIDs[i].fourth = 0;
                netIDs[i].third += 1;
            }
            if(netIDs[i].third == 256)
            {
                netIDs[i].third = 0;
                netIDs[i].second += 1;
            }


            firstUsables[i] = netIDs[i] ;lastUsables[i] =netIDs[i]; bradCasts[i] = netIDs[i];

            firstUsables[i].fourth = netIDs[i].fourth+1;
            lastUsables[i].fourth  = netIDs[i].fourth+hosts;
            bradCasts[i].fourth    = netIDs[i].fourth+hosts + 1;

        }else if(hosts>256 && hosts<= (256*256))
        {

            if(i!=0)
            {
                netIDs[i].third  = netIDs[i - 1].third + (hops/256);
                netIDs[i].second = netIDs[i - 1].second ;
            }
            if(netIDs[i].third == 256)
            {
                netIDs[i].third = 0;
                netIDs[i].second += 1;
            }

            firstUsables[i] = netIDs[i] ;lastUsables[i] =netIDs[i]; bradCasts[i] = netIDs[i];
            firstUsables[i].fourth = netIDs[i].fourth+1;

            lastUsables[i].third   = netIDs[i].third+(hops/256)-1;
            lastUsables[i].fourth  = 254;

            bradCasts[i].third     = lastUsables[i].third;
            bradCasts[i].fourth    = 255;

        }


        else if(hosts>(256*256))
        {
            if(i!=0)
            {
                netIDs[i].second = netIDs[i - 1].second + hops/(256*256);
            }

            firstUsables[i] = netIDs[i] ;lastUsables[i] =netIDs[i]; bradCasts[i] = netIDs[i];

            firstUsables[i].fourth   = 1;

            lastUsables[i].second   += hops/(256*256)-1;
            lastUsables[i].third     = 255;
            lastUsables[i].fourth    = 254;

            bradCasts[i].second      = lastUsables[i].second;
            bradCasts[i].third       = 255;
            bradCasts[i].fourth      = 255;

        }


    }

    if(way=='h' || way=='n' || way=='b' )
        print(netIDs, firstUsables,  lastUsables,  bradCasts,  subnets,  bits,  hosts,  hops,  mask);

    delete[] netIDs;
    delete[] firstUsables;
    delete[] lastUsables;
    delete[] bradCasts;
}


int main()
{

// User input.
    string row_ip;
    char way;
    int number;

// Calling the interface, initialising row_ip , way , number.
    interface(row_ip,way,number);

// Instantiating object from IP Class.
    IP my_ip = row_ip;

    if(my_ip.findClass() == 'C' )
        classC(my_ip,way,number);  // Calling the class C function.
    else if ((my_ip.findClass() == 'B') )
        classB(my_ip,way,number);  // Calling the class B function.
    else if ((my_ip.findClass() == 'A') )
        classA(my_ip,way,number);  // Calling the class A function.














}

