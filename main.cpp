#include<bits/stdc++.h>
#include<strstream>
using namespace std;
struct electronics
{


    float  price ;
    char name[30];
    char id[20];
    char brand [30];

};

void openf(fstream & f)
{
    f.open( "mezo.txt" , ios::out|ios::in) ;
}
void openf1(fstream & f)
{
    f.open( "elndefa.txt" , ios::in|ios::out) ;
}
istream& operator >>(istream  &in , electronics &ad);
void add( fstream &stream,electronics ad);
short find1( fstream& f , char id[] );
void delete1( fstream& f , char id[] );
void write_to_f(fstream& f , electronics ad);
ostream& operator<<( ostream & out, electronics &ad );


ostream& operator<<( ostream & out, electronics &ad )
{

    out << "ID: " << ad.id << endl ;
    out << "Brand: " << ad.brand << endl ;
    out<<"name: "<<ad.name<<endl;
    out<<"price: "<<ad.price<<endl;
    return out ;
}


istream& operator >>(istream  &in , electronics &ad)
{
    cout<<"id is ";
    in.getline(ad.id,20);
    cout<<endl;
    cout<<"brand is ";
    in.getline(ad.brand,30);
    cout<<endl;
    cout<<"name is ";
    in.getline(ad.name,30);
    cout<<endl;
    cout<<"price is ";
    in>>ad.price;
    return in;


}

void add ( fstream &f, electronics ad)
{
    char record[150];
    char s[50];
    stringstream fizpo;
    fizpo<<ad.price;
    fizpo>>s;
    strcpy(record, ad.id);
    strcat(record, "#");
    strcat(record, ad.brand);
    strcat(record, "#");
    strcat(record,ad.name);
    strcat(record, "#");
    strcat(record,s);
    strcat(record, "#");

    openf(f);
    bool k = false ;
    short avl ;
    f.seekg(0,ios::beg) ;
    f.read((char*)&avl,sizeof(avl)) ;
    f.close();
    short len = strlen(record) ;

    if( avl==-1 )
    {
        openf(f);
        f.seekp(0,ios::end) ;
        short nxt = -2;
        f.write((char*)&nxt,sizeof(nxt)) ;
        f.write((char*)&len,sizeof(len)) ;
        f.write(record,len) ;
        f.close();
        k = true ;
    }
    else
    {
        openf(f);
        short next , Size;
        f.seekg(avl,ios::beg) ;
        f.read((char*)&next,sizeof next);
        f.read((char*)&Size,sizeof Size);
        f.close();
        bool a=true;
        while (a)
        {
            if (len<=Size)
            {
                openf(f);
                f.seekp(avl,ios::beg) ;
                short nxt = -2;
                f.write((char*)&nxt,sizeof(nxt)) ;
                f.write((char*)&len,sizeof(len)) ;
                f.write(record,len) ;
                f.close();
                openf(f);
                f.seekp(0,ios::beg);
                f.write((char*)&next,sizeof(next)) ;
                next=0;
                f.write((char*)&next,sizeof(next)) ;
                f.close();

                a=false;
            }
            else
            {
                openf(f);
                f.seekp(avl,ios::beg) ;
                short net,siz;
                f.read((char*)&net,sizeof net);
                f.read((char*)&siz,sizeof siz);
                f.close();
                avl=next;
                next=net;
                Size=siz;
            }

        }
    }

    return;
}


short find1( fstream& f , char *d )
{
    openf(f);
    f.seekg(0,ios::beg) ;
    short l , nxt;
    char buff[150]  = {0};
    char tmp[20] = {0};
    while( !f.eof() )
    {
        short pos = f.tellp();
        f.read((char*)&nxt,sizeof(nxt)) ;
        if( f.eof() )
        {
            break ;
        }
        f.read((char*)&l,sizeof(l)) ;
        f.read(buff,l) ;
        for(int i = 0 ; i < l; i++)
        {
            if(buff[i] == '#')
                break;
            tmp[i] = buff[i];
        }
        if(strcmp(tmp, d) ==0 )
        {
            f.close();
            return pos;
        }
    }
    f.close();
    cout << "The record is not found!!" << endl ;
    return -1;
}
void delete1( fstream& f , char *id )
{
    short ofsset = find1(f,id) ;
    openf(f);
    f.seekp(0,ios::beg);
    short nxt,reco;
    short l=f.tellp();
    f.read((char*)&nxt,sizeof nxt);
    f.seekg(ofsset,ios::beg);
    f.read((char*)&reco,sizeof reco);
    if(reco!=-2)
    {
        cout<<"the record deleted before"<<endl;
        f.close();
        return;
    }
    f.close();
    openf(f);
    f.seekg(0,ios::beg);
    short t=nxt;
    nxt=ofsset;
    f.write((char*)&nxt,sizeof nxt);
    f.seekg(ofsset,ios::beg);
    ofsset=t;
    f.write((char*)&ofsset,sizeof ofsset);
    f.close();

}

void update(fstream &f,char *id)
{

    short offset= find1(f,id);
    openf(f);
    cin.ignore();
    electronics ad;
    cin>>ad;

    f.seekp(offset, ios::beg);
    short m,len;
    f.read((char *) &m, sizeof m);
    f.read((char *) &len, sizeof len);
    f.close();

    char record[150];
    char s[50];
    stringstream fizpo;
    fizpo<<ad.price;
    fizpo>>s;
    strcpy(record, ad.id);
    strcat(record, "#");
    strcat(record, ad.brand);
    strcat(record, "#");
    strcat(record,ad.name);
    strcat(record, "#");
    strcat(record,s);
    strcat(record, "#");

    short len1 = strlen(record);

    if (len1 <=len)
    {
        openf(f);
        f.seekp(offset, ios::beg);
        short l = -2;
        f.write((char *) &l, sizeof l);
        f.write((char *) &len1, sizeof len1);
        f.write(record, len1);
        f.close();
        return ;
    }
    else if(len1>len)
    {
        delete1(f,id);
        openf(f);

        f.seekg(0,ios::end) ;
        short l = -2;
        f.write((char *) &l, sizeof l);
        f.write((char *) &len1, sizeof len1);
        f.write(record, len1);
        f.close();

    }

}
void compactFile(fstream& f,fstream& w)
{
    w.open("elndafa.txt", ios::trunc|ios::out);
    f.open("mezo.txt", ios::out|ios::in);

    short header;
    f.seekp(0,ios::beg);
    f.read((char *) &header, sizeof header);
    f.seekg(2,ios::cur);

    cout<<header;

    short  s,a = f.tellp(),h=0;

}
int main()
{
    fstream f,w;
    f.open( "mezo.txt" , ios::out|ios::in|ios::trunc ) ;
    short avl = -1 ;
    f.seekp(0,ios::beg) ;
    f.write( (char*)&avl,sizeof(avl) ) ;
    avl = 0;
    f.write( (char*)&avl,sizeof(avl) ) ;
    f.close();
    electronics ad;
    bool k=true;
    short n;
    while (k)
    {
        cout<<"1) add "<<endl;
        cout<<"2) update "<<endl;
        cout<<"3) delete "<<endl;
        cout<<"4) search "<<endl;
        cout<<"5) compact "<<endl;
        cout<<"6) exit "<<endl;
        cin >>n;
        cin.ignore();
        if (n==1)
        {
            cin>>ad;
            add(f,ad);
        }
        else  if (n==2)
        {
            cout<<"what 'is id of device ";
            cin>>ad.id;
            update(f,ad.id);
        }
        else if (n==3)
        {
            cout<<"what 'is id of device ";
            cin>>ad.id;
            delete1(f,ad.id);
        }
        else if (n==4)
        {
            cout<<"what 'is id of device ";
            cin>>ad.id;
            char buff[200] = { 0 };
            short l ;
            short pos=find1(f,ad.id);
            if(pos != -1)
            {
                openf(f);
                f.seekp(pos,ios::beg);
                f.read((char*)&l,sizeof l);
                f.read((char*)&l,sizeof l);
                f.read((char*)&buff,l);
                f.close();
                for(int i =  0 ; i < l; i++)
                {
                    if(buff[i] == '#')
                    {
                        cout<<endl;
                        continue;
                    }
                    cout<<buff[i] ;
                }
            }
        }
        else if( n == 5)
        {
            f.close();
            w.close();
            compactFile(f,w);
        }
        else  if (n==6)
        {
            cout<<"the f exit :D ";
            k=false;
        }
        else
        {
            cout<<"please choose again ,, wrong choise "<<endl;
            cin>>n;
        }
    }
    return 0;
}
