#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>

using namespace std;

int chk=0,o,choice[1000] ;

class BIN
{
    int admno ;
    int rollno ;
    char name[30] ;
    char sec ;
    int clas ;
    char strm[20] ;
    int sub ;
    int M[5] ;
    int ttlm[1000] ;
    float per[1000] ;
    char OG[1][1000] ;

public:

    BIN()
    {
        admno=0 ;
        rollno=0 ;
        strcpy(name,"NULL") ;
        sec='A' ;
        clas=0 ;
        strcpy(strm,"Not Applicable") ;
        sub=5 ;
        for(int i=0; i<1000 ; i++)
        {
            M[i]=0 ;
            ttlm[i]=0 ;
            per[i]=0 ;
            OG[0][i]='A' ;
        }
    }

    void Assign()
        {
            if(per[admno]>=95)
            {
                OG[0][admno]='A' ;
            }
            else if(per[admno]>=90 && per[admno]<=94.9)
            {
                OG[0][admno]='A' ;
            }
            else if(per[admno]>=80 && per[admno]<=89.9)
            {
                OG[0][admno]='B' ;
            }
            else if(per[admno]>=70 && per[admno]<=79.9)
            {
                OG[0][admno]='C' ;
            }
            else if(per[admno]>=60 && per[admno]<=69.9)
            {
                OG[0][admno]='D' ;
            }
            else if(per[admno]>=50 && per[admno]<=59.9)
            {
                OG[0][admno]='E' ;
            }
            else if(per[admno]<=49.9)
            {
                OG[0][admno]='F' ;
            }
        }

    void ADDM()
    {
            cout << "Kindly Enter Admission Number :" << endl ;
            cin >> admno ;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
            cout << "Enter Marks For :" << endl ;
            for(int i=0; i<sub ; i++)
            {
                cout << "Subject " << i+1 << " : " << endl ;
                cin >>M[i] ;
                ttlm[admno]+=M[i] ;
            }
            per[admno]=ttlm[admno]/sub ;
            Assign() ;
            cout << "Marks Added Successfully!" << endl ;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
            cout << endl ;
            choice[admno]=1 ;
    }

    void ADD()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << "\t\t\tKindly Enter Admission Number After :" << o << endl ;
        cout << "\t\t\tEnter Admission Number :" << endl ;
        cin >> admno ;
//        while(o>=0)
//        if(SUAN()==admno)
//        {
//            cout << "Kindly Re-Enter The Admission Number as " << admno << " Already Exist." << endl ;
//            cin >> admno ;
//            o-- ;
//        }
        cout << "\t\t\tEnter Name :" << endl ;
        cin.ignore() ;
        gets(name) ;
        cout << "\t\t\tKindly Enter Roll Number After :" << o << endl ;
        cout << "\t\t\tEnter Roll Number :" << endl ;
        cin >> rollno ;
        cout << "\t\t\tEnter Class :" << endl ;
        cin >> clas ;
        cout << "\t\t\tEnter Section :" << endl ;
        cin >> sec ;
        if(clas>10)
        {
            cout << "\t\t\tEnter Stream" << endl ;
            cin.ignore() ;
            gets(strm) ;
        }
        cout << "\t\t\tData Added Successfully." << endl ;
        //cout << "Do You Want To Enter Marks (1 for Yes || 0 for NO) ?" << endl ;
        //cin >> choice[admno] ;
        //if(choice[admno]==1)
        //{
        // ADDM() ;
        //}
        o++ ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl ;
    }

    void CHCK() ;

    void DISP()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << "\t\t\tAdmission Number :" << admno << endl ;
        cout << "\t\t\tName :" ;
        puts(name) ;
        cout << "\t\t\tRoll Number :" << rollno << endl ;
        cout << "\t\t\tClass :" << clas << endl ;
        cout << "\t\t\tSection :" << sec << endl ;
        cout << "\t\t\tStream :" << strm << endl ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl ;
    }
    void DISPM()
    {
        if(choice[admno]==1)
       {
       cout << "Total Subjects : " << sub << endl ;
        for(int i=0; i<sub; i++)
       {
       cout << "Marks for Subject " << i+1 << " :" << M[i] << endl ;
        }
        cout << "Total Marks : " << ttlm[admno] << endl ;
        cout << "Percentage : " << per[admno] << endl ;
        cout << "Grade : " << OG[o][admno] << endl ;
        }
        else
        {
            cout << "Marks Not Entered Yet!" << endl ;
        }
          cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
          cout << endl ;
    }

    void SRCH1() ;

    void SRCH2() ;

    void SRCH3() ;

    void MODAN() ;

    void MODN() ;

    void MODRN() ;

    int SUAN()
    {
        return admno ;
    }

    int SURN()
    {
        return rollno ;
    }

    char* SUN()
    {
        return name ;
    }
};

    void CHCK()
    {
        BIN B ;
       fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
       while(f.read((char*)&B,sizeof(B)))
        {
            o++ ;
        }
        f.close() ;
    }

    void BIN::SRCH1()
    {
       cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
       BIN B ;
       int x ;
       cout << "Kindly Enter Admission Number :" << endl ;
       cin >> x ;
       cout << endl ;
       fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
       while(f.read((char*)&B,sizeof(B)))
        {
            if(B.SUAN()==x)
            {
                B.DISP() ;
                //B.DISPM() ;
                chk++ ;
            }
        }
        f.close() ;
        if(chk==0)
        {
           cout << "Not Found" << endl ;
           cout << endl ;
        }
        chk=0 ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl ;
    }

    void BIN::SRCH2()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        int y ;
        BIN B ;
        cout << "Kindly Enter Roll Number :" << endl ;
        cin >> y ;
        cout << endl ;
        fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
        while(f.read((char*)&B,sizeof(B)))
        {
            if(B.SURN()==y)
            {
                B.DISP() ;
                //B.DISPM() ;
                chk++ ;
            }
        }
        f.close() ;
        if(chk==0)
        {
            cout << "Not Found" << endl ;
            cout<< endl ;
        }
        chk=0 ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl ;
    }

    void BIN::SRCH3()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        BIN B ;
        char n[30] ;
        cout << "Kindly Enter Name :" << endl ;
        cin.ignore() ;
        gets(n) ;
        cout << endl ;
        fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
        while(f.read((char*)&B,sizeof(B)))
        {
            if(strcmpi(B.SUN(),n)==0)
            {
                B.DISP() ;
                //B.DISPM() ;
                chk++ ;
            }
        }
        if(chk==0)
        {
            cout << "Not Found" << endl ;
            cout << endl ;
        }
        chk=0 ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        cout << endl ;
        f.close() ;
    }

    void BIN::MODAN()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        BIN B ;
        int ca,x ;
        cout << "Kindly Enter The Old Admission Number :" << endl ;
        cin >> x ;
        fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
        while(f.read((char*)&B,sizeof(B)))
        {
            if(B.SUAN()==x)
            {
                f.seekg(0,ios::cur) ;
                cout << "Enter New Details :" << endl ;
                B.ADD() ;
                int loc=f.tellg()-sizeof(B) ;
                f.seekp(loc) ;
                f.write((char*)&B,sizeof(B)) ;
            }
        }
        f.close() ;
        o-- ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
    }

    void BIN::MODN()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        BIN B ;
        int ca ;
        char n[30] ;
        cout << "Kindly Enter The Name :" << endl ;
        cin.ignore() ;
        gets(n) ;
        fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
        while(f.read((char*)&B,sizeof(B)))
        {
            if(strcmpi(B.SUN(),n)==0)
            {
                f.seekg(0,ios::cur) ;
                cout << "Enter New Details :" << endl ;
                B.ADD() ;
                int loc=f.tellg()-sizeof(B) ;
                f.seekp(loc) ;
                f.write((char*)&B,sizeof(B)) ;
            }
        }
        f.close() ;
        o-- ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
    }

    void BIN::MODRN()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
        BIN B ;
        int x ;
        cout << "Kindly Enter The Old Roll Number :" << endl ;
        cin >> x ;
        fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary) ;
        while(f.read((char*)&B,sizeof(B)))
        {
            if(B.SURN()==x)
            {
                f.seekg(0,ios::cur) ;
                cout << "Enter New Details :" << endl ;
                B.ADD() ;
                int loc=f.tellg()-sizeof(B) ;
                f.seekp(loc) ;
                f.write((char*)&B,sizeof(B)) ;
            }
        }
        f.close() ;
        o-- ;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
    }


int main()
{
    BIN B ;
    int c,c1,c2,c3 ;
    CHCK() ;
    do
    {
        cout << "\t\t\t1. Enter Details." << endl ;
        cout << "\t\t\t2. View Details Using Search." << endl ;
        cout << "\t\t\t3. Modify Details." << endl ;
        cout << "\t\t\t4. To See The Total Number Of Records Present." << endl ;
        cout << "\t\t\t0. Exit." << endl ;
        cout << "\t\t\tKindly Enter Your Choice:" << endl ;
        cin >> c ;
        cout << endl ;
        switch(c)
        {
            case 1:
                {
                    system("cls");
                    fstream f("SCHOOL.dat", ios::in | ios::out | ios::binary | ios::app) ;
                    B.ADD() ;
                    f.write((char*)&B,sizeof(B)) ;
                    f.close() ;
                }
            break ;
            case 2:
                {
                    system("cls");
                    cout << "\t\t\t5. Search Using Admission Number.\t\t\t" << endl ;
                    cout << "\t\t\t6. Search Using Roll Number." << endl ;
                    cout << "\t\t\t7. Search Using Name." << endl ;
                    cout << "\t\t\tKindly Enter Your Choice :" << endl ;
                    cin >> c1 ;
                    cout << endl ;
                    switch(c1)
                    {
                    case 5:
                        {
                           system("cls");
                           B.SRCH1() ;
                        }
                    break ;
                    case 6:
                        {
                           system("cls");
                           B.SRCH2() ;
                        }
                        break ;
                    case 7:
                        {
                           system("cls");
                           B.SRCH3() ;
                        }
                        break ;
                    }
                }
                break ;
                case 3:
                    {
                        system("cls");
                        cout << "\t\t\tKindly Enter What Would You Like To Modify ?" << endl ;
                        cout << "\t\t\t8.Admission Number." << endl ;
                        cout << "\t\t\t9.Name." << endl ;
                        cout << "\t\t\t10.Roll Number." << endl ;
                        cout << "\t\t\t11.Class." << endl ;
                        cout << "\t\t\t12.Section." << endl ;
                        cout << "\t\t\t13.Stream." << endl ;
                        cin >> c2 ;
                        switch(c2)
                        {
                        case 8:
                            {
                                system("cls");
                                B.MODAN() ;
                            }
                            break ;
                        case 9:
                            {
                                system("cls");
                                B.MODN() ;
                            }
                            break ;
                        case 10:
                            {
                                system("cls");
                                B.MODRN() ;
                            }
                            break ;
                        case 11:
                            {
                        system("cls");
                        cout << "\t\t\tWhat Would You Like To Enter ?" << endl ;
                        cout << "\t\t\t14.Admission Number." << endl ;
                        cout << "\t\t\t15.Name." << endl ;
                        cout << "\t\t\t16.Roll Number." << endl ;
                        cin >> c3 ;
                        switch(c3)
                        {
                        case 14 :
                            {
                                system("cls");
                                B.MODAN() ;
                            }
                            break ;
                        case 15:
                            {
                                system("cls");
                                B.MODN() ;
                            }
                            break ;
                        case 16:
                            {
                                system("cls");
                                B.MODRN() ;
                            }
                            break ;
                        }
                            }
                            break ;
                        case 12:
                            {
                        system("cls");
                        cout << "\t\t\tWhat Would You Like To Enter ?" << endl ;
                        cout << "\t\t\t14.Admission Number." << endl ;
                        cout << "\t\t\t15.Name." << endl ;
                        cout << "\t\t\t16.Roll Number." << endl ;
                        cin >> c3 ;
                        switch(c3)
                        {
                        case 14 :
                            {
                                system("cls");
                                B.MODAN() ;
                            }
                            break ;
                        case 15:
                            {
                                system("cls");
                                B.MODN() ;
                            }
                            break ;
                        case 16:
                            {
                                system("cls");
                                B.MODRN() ;
                            }
                            break ;
                        }
                            }
                            break ;
                        case 13:
                            {
                                system("cls");
                        cout << "\t\t\tWhat Would You Like To Enter ?" << endl ;
                        cout << "\t\t\t14.Admission Number." << endl ;
                        cout << "\t\t\t15.Name." << endl ;
                        cout << "\t\t\t16.Roll Number." << endl ;
                        cin >> c3 ;
                        switch(c3)
                        {
                        case 14 :
                            {
                                system("cls");
                                B.MODAN() ;
                            }
                            break ;
                        case 15:
                            {
                                system("cls");
                                B.MODN() ;
                            }
                            break ;
                        case 16:
                            {
                                system("cls");
                                B.MODRN() ;
                            }
                            break ;
                        }
                            }
                            break ;
                        }
                    }
                        break ;
            case 4:
                  {
                    system("cls");
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                    cout << "The Total Number Of Records Present in The Database Are :" << o << endl ;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                    cout << endl ;
                  }
                        break ;
            case 0:
                {
                    system("cls");
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                    cout << "\t\t\tThank You For Using The Program!" << endl ;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                    exit(0) ;
                }
                break ;
                default:
                    {
                        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                        cout << "\t\t\tInvalid Choice" << endl ;
                        cout << "------------------------------------------------------------------------------------------------------------------------" << endl ;
                        cout << endl ;
                    }
        }
    }while(c!=0) ;
    getchar() ;
    return 0 ;
}

