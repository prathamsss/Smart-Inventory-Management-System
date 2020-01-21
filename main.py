import pandas as pd
import json
from firebase import firebase
import requests
import time
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import tkinter as tk
from tkinter import *


def data_entry(quantity):
    #label3=Label(frame2,font='Times 20 bold',fg="red",text='Here is your invoice').place(x=24,y=178)
    nm=list(it.keys())
    dict = {'name': nm, 'quantity': quantity} 
    print(dict)
    df = pd.DataFrame(dict) 
    df.to_csv('data.csv') 
def csv_open():
    df=pd.read_csv('data.csv')
    print("File openned secessfully")
    
def email():
    mail_content = """Hello, This is your inventry !! Here's your invoice !! Kindly check !
    THIS IS SYSTEM GENERATED EMAIL PLEASE DO NOT REPLAY!!
    """

    #The mail addresses and password
    sender_address = 'pratham.sardeshmukh@gmail.com'
    sender_pass = 'Dada@123123'
    receiver_address = 'chimu.sardeshmukh42@gmail.com'
    #Setup the MIME
    message = MIMEMultipart()
    message['From'] = sender_address
    message['To'] = receiver_address
    message['Subject'] = 'Inventry Invoice'
    #The subject line
    #The body and the attachments for the mail
    message.attach(MIMEText(mail_content, 'plain'))
    attach_file_name = 'data.csv'
    attach_file = open(attach_file_name, 'rb') # Open the file as binary mode
    payload = MIMEBase('application', 'octate-stream')
    payload.set_payload((attach_file).read())
    encoders.encode_base64(payload) #encode the attachment
    #add payload header with filename
    payload.add_header('Content-Decomposition', 'attachment', filename=attach_file_name)
    message.attach(payload)
    #Create SMTP session for sending the mail
    session = smtplib.SMTP('smtp.gmail.com', 587) #use gmail with port
    session.starttls() #enable security
    session.login(sender_address, sender_pass) #login with mail_id and password
    text = message.as_string()
    session.sendmail(sender_address, receiver_address, text)
    session.quit()
    print('Mail Sent')
        
    
    
fire = firebase.FirebaseApplication('https://pratham-2307.firebaseio.com/DHT11', None)


i_1= (fire.get('/i_1', None))
i_2= (fire.get('/i_2', None))
i_3= (fire.get('/i_3', None))


i_1= int(i_1)
i_2= int(i_2)
i_3= int(i_3)
print(type(i_1))
print(i_1)
it={'nut : ':i_1,'bolt : ':i_2, 'screw : ': i_3}
items=list(it.values())
#
print(items)




total=[800 ,800 ,600]
th=[200 ,0, 200 ]
quantity=[]


print("Welcome to Smart Inventry Manager ")

#frame2=Tk()
#frame2.geometry("4000x2000")
#frame2.title('Inventry Managaement Sysytem ')
#label3=Label(frame2,font='Times 20 bold',fg="red",text='Welcome To Your Inventory Management').place(x=24,y=15)

#w=input("To Add new entry press 1")




count=0
for i in range(int(len(items))):
    if items[i]>=th[i]:
        quantity.append(total[i]-items[i])
        count=count+1
        print("It seems your item ",count ,"are getting over")
        #label4=Label(frame2,font='Times 20 bold',fg="blue",text='It seems your items are getting over').place(x=50,y=75)

    else:
        quantity.append(0)    
print(quantity)
w=input("Place an order ?")
#abel5=Label(frame2,font='Times 20 bold',fg="green",text='Place an order ?').place(x=50,y=100)
#B = tk.Button(frame2,text ="y", command = data_entry).place(x=50,y=135)

if w=='y':
    data_entry(quantity) 
    word=input("Check invoice?")
    if word=='y':

        csv_open()
        time.sleep(3)
        print("Order placed successfully")
        email()
    elif word=='n':
        print("Order placed successfully")
    #email()
        
        
else: 
    print("Thank you")  
        
    
    




#def whats_app_text():
#    account_sid = 'AC650bb04a085b059fd05aa92cd69a8d8e'
#    auth_token = 'f131b37a1cd02f0f3235254eac4ffaa6'
#    client = Client(account_sid, auth_token)
#
#    message = client.messages.create(
#                              body=[{quantity_i_1}],
#                              from_='whatsapp:+14155238886',
#                              to='whatsapp:+917350770905'
#                          )    
             
import matplotlib.pyplot as plt 

day=1    #time == 12.00am
incoming_stock=[]
outgoing_stock=[10,20,30]

total=[20,30,50]

remain=[]
for i in range(0,3):
   remain.append(total[i]-outgoing_stock[i])

plt.plot(total,outgoing_stock)

plt.xlabel('total') 
plt.ylabel('outgoing_stock') 
#frame2.mainloop()
#B.pack()







    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
