#include<iostream>
#include<fstream>
#include<sstream>
#include <stdlib.h>
#include <string.h>
#define max 100000
using namespace std;

int main()
{
    string a[max];

    fstream file;

    string word,t,q,filename,sm;

    char de[5],s[5],st[5],str1[5];

    int cnt=1,n=0,len=0,date=0,aa=0,curr,an=0,the=0,c=0,d,m,y,go=1,para=0,kp=0;

    char ch;

    string str[24]= {"january","jan","feb","february","march","mar","april","apr","may","june","jun","july","jul","august","aug","september","sep","october","oct","november","nov","december","dec"};


    cout<<"Enter filename : ";
    cin>>filename;

    file.open (filename.c_str());
    while(!file.eof())
    {

        file.get(ch);
        para=int(ch);
        file.seekg(-4,ios::cur);
        file<<" ";
        file.seekg(-3,ios::cur);
        file<<" ";
        para=para-48;
        cout<<para<<" paragraphs : "<<endl;
        break;

    }
    file.close();



    file.open (filename.c_str());
    while(!file.eof()&&kp<=para)
    {
        file.get(ch);
        if(ch=='\n'&&kp==0)
        {
            sm.clear();
            kp++;
            continue;
        }
        if(ch=='\n')
        {
x:
            istringstream iss(sm);
            while(iss >> word)
            {
                //cout<<word;
                len=word.size();
                for(int j=0; j<len; j++)
                {
                    word[j]=tolower(word[j]);       //case insensitive approach

                }
                a[n]=word;                          //store word in to an array
                n++;                                //increment array bound
            }

            for(int i=0; i<n; i++)                  //loop for articles
            {
                word=a[i];
                if(word=="a")
                    aa++;
                if(word=="an")
                    an++;
                if(word=="the")
                    the++;
                /*-----------------------------------------------
                  Date format : mm/dd/yy or dd/mm/yy etc. handled
                  -----------------------------------------------
                */
                len=word.size();
                if(len>=6)
                {
                    //checking if in the format of / and -
                    for(int i=0; i<len; i++)
                    {
                        if(word[i]=='/'||word[i]=='-')
                            c++;
                    }
                    // if it has the following symbol possibly its a date
                    if(c==2)
                    {
                        for(int i=0; i<len; i++)
                        {
                            if(word[i]=='/'||word[i]=='-')
                                continue;
                            //if the characters except the symbols are numeric its a date
                            else if(isdigit(word[i]))
                            {
                                c++;
                            }
                            else
                            {
                                c=0;
                                break;
                            }
                        }
                        int j=0;
                        for(int i=0; i<=len; i++)
                        {

                            static int cnt=0;
                            if(word[i]=='/'||word[i]=='-')
                            {
                                de[j++]='\0';
                                cnt++;
                                if(cnt==1)
                                    strcpy(s,de);
                                if(cnt==2)
                                    strcpy(st,de);
                                j=0;
                            }
                            //if the characters except the symbols are numeric its a date
                            else
                                de[j++]=word[i];
                        }
                        de[j]='\0';
                        strcpy(str1,de);
                    }
                }
                c=c-2;
                if(c>0)
                {
                    d=atoi(s);
                    m=atoi(st);
                    y=atoi(str1);           //see if valid dates are inputted
                    if(d<=31&&m<=12||d<=12&&m<=31)
                    {
                        if(d==2||m==2)      //if month is February
                        {
                            if(((y%4==0)&&(y%100!=0))||(y%400==0))
                            {
                                //check leap year conditions
                                if((m<=29)&&(d<=29))
                                    date++;
                            }
                            else
                            {
                                //validity of date
                                if((m<=28)&&(d<=28))
                                    date++;
                            }
                        }
                        else
                        {
                            date++;
                            //cout<<d<<"/"<<m<<"/"<<y<<endl;
                        }
                    }
                }
                c=0;
                /*--------------------------------------------
                   Date formats handled
                  --------------------------------------------
                */
            }
            /*-----------------------------------------------------
              Date format : 12 jul 2014 , july 12 2014 etc. handled
              -----------------------------------------------------
            */
            int k=2;
            while(k!=n)
            {
                string pre,next,ppre,cur;
                ppre=a[k-2];            //previous to previous word
                pre=a[k-1];             //previous word
                next=a[k+1];            //next word
                curr=k;                 //current index
                for(int j=0; j<=24; j++)//check in the month array
                {
                    if(a[curr]==str[j])
                    {
                        if(isdigit(pre[0])||isdigit(next[0])||isdigit(ppre[0]))
                        {
                            // cout<<endl<<pre<<" "<<a[curr]<<" "<<next;
                            date++;
                            k=k+2;
                            break;
                        }
                    }
                }
                k++;
            }
            /*--------------------------------------------
               Date formats handled
              --------------------------------------------
            */
            cout<<aa<<" "<<an<<" "<<the<<" "<<date<<endl;
            aa=0;
            an=0;
            the=0;
            date=0;
            cnt=1;
            c=0;
            n=0;
            sm.clear();
            kp++;
        }
        else
            sm+=ch;

    }
    if(go==1)
    {
        go++;
        goto x;
    }
}


