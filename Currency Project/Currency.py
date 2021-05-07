#importing Libraries
import urllib.request, urllib.parse, urllib.error
import json
import ssl

#Kindly Check For The API Key
#If You Do Not Have One, Kindly Obtain at http://api.forex/products
#Once You Obtain Your API Key, Change it To True
#api_key = True
api_key = False

while True:
    print('\n')
    #Asking User For Source For Conversions
    x=input('Kindly Enter From Which Source You Would Like To Convert The Currency:\n1.File\n2.Web\n0.Quit\n')
    x=int(x)

    #Checking if User Doesnt Have API Key
    if x==1 :
        #Reading The JSON File
        fname = 'Cur.json'
        data = open(fname).read()
    elif x==2 :
        #Checking For API Key
        if api_key is False:
             print('Kindly Obtain The API Key.')
             print('You Will Quit Now...')
             exit(0)
        else :
             serviceurl = 'https://v2.api.forex/rates/latest.json?beautify=true&key='
             #Place Your API Key After The 'key=' in the above URL
    elif x==0:
        #To Exit
        print('Thank You For Using The Program!')
        exit(0)
    else :
        print('Invalid Input, You Will Quit Now')
        exit(0)

    #Ignore SSL certificate errors
    if x==2 :
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE

    #To Enter All The Details
    print('If You Want To Quit, Just Press Enter.')
    print('\nKindly Enter The Currency in The Format: \nFor US Dollars as USD, \nFor Indian Rupees as INR, \nFor Canadian Dollars as CAD \nand so on...')
    print('§!THIS PROGRAM IS NOT CASE SENSITIVE!§')
    a=input('Enter The Currency From Which You Would Like To Convert : ')
    if len(a) < 1:
        #To Exit
        print('Thank You For Using The Program!')
        break
    b=input('Enter The Currency You Would Like To Convert To : ')
    c=input('Enter The Amount To Be Converted : ')
    #To Convert String To Float(Decimal Value)
    c=float(c)
    #To Uppercase All Characters
    a=a.upper()
    b=b.upper()

    if x==2:
        #Retrieving The URL
        print('Retrieving', url)
        uh = urllib.request.urlopen(url, context=ctx)
        data = uh.read().decode()
    #To Print The Amount of Characters Recieved
    print('Retrieved', len(data), 'characters\n')

    #Checking If JSON Data is Obtained Well or not
    try:
        js = json.loads(data)
    except:
        js = None

    #if Data is Not Obtained, It Quits
    if not js or 'success' not in js or js['success'] != True:
        print('==== Failure To Retrieve ====')
        print(data)
        continue

    #Retrieving The Data And Doing Calculations
    cl=js['infos']['usage']['api_count']
    date=js['infos']['date']
    time=js['infos']['timestamp']

    #Checking If Value is USD as Base is USD
    #Also Checking If The Currency Entered is Right or Not
    if a == 'USD' :
        val_a=1.000
    else :
        try :
            val_a=js['rates_histo'][a]['close']
        except:
            print('Invaild Currency Entered(1)')
            break
    val_a=float(val_a)
    val_c=c/val_a
    if b == 'USD' :
        val_b=1.000
    else :
        try :
            val_b=js['rates_histo'][b]['close']
        except:
            print('Invaild Currency Entered(2)')
            break
    val_b=float(val_b)
    val_c=val_c*val_b

    #Printing Data To The User
    print('***************\n')
    print('Conversions Left For This Month :', cl)
    print('Date :',date)
    print('Time-Stamp(UTC) :', time[11:])
    print('You Converted', a, c, 'to', b,)
    print('Converted Amount :', b, val_c)
    print('Rate at Which Conveted :',a, val_a, '/USD', ',', b, val_b, '/USD' )
    print(a, '/', b , ':', val_a/val_b)
    print(b, '/', a , ':', val_b/val_a)
    print('With 5% Increment :', val_c*1.05)
    print('With 10% Increment :', val_c*1.1, '\n')
    print('***************')
