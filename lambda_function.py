#Amazon Web Service Lambda function for sending emails after recieving a post request,adapted from an AWS template for http dynamoDB access

import boto3
import json


import smtplib
print('Loading function')
dynamo = boto3.client('dynamodb')


def respond(err, res=None):
    return {
        'statusCode': '400' if err else '200',
        'body': err.message if err else json.dumps(res),
        'headers': {
            'Content-Type': 'application/json',
        },
    }


def lambda_handler(event, context):
    '''Demonstrates a simple HTTP endpoint using API Gateway. You have full
    access to the request and response payload, including headers and
    status code.

    To scan a DynamoDB table, make a GET request with the TableName as a
    query string parameter. To put, update, or delete an item, make a POST,
    PUT, or DELETE request respectively, passing in the payload to the
    DynamoDB API as a JSON body.
    '''
    #print("Received event: " + json.dumps(event, indent=2))

    operations = {
        'POST': sendMail(event['body']),
    }

    operation = event['httpMethod']
    if operation in operations:
        print (event)
       # email = getEmailAddress(event[body])
        #message = getMessage(event[body])
        operations[operation]
       



def sendMail(body):
    data = json.loads(body)
    gmail_user = 'khbjh179@gmail.com'
    gmail_password = '_cpsc441'
    
    sent_from = gmail_user
    to = data.get('emailAddress')
    subject = 'Notification'
    body = data.get('message')
    
    email_text = ("From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s" %(sent_from, to, subject, body))
    
    
    try:
        server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
        server.ehlo()
        #server = smtplib.SMTP('smtp.gmail.com', 587)
        #server.starttls()
        server.login(gmail_user, gmail_password)
        server.sendmail(sent_from, to, email_text)
        #server.sendmail(sent_from, to, message)
        #server.quit()
        server.close()
        print ('Email sent!')
    except:
        print ('Something went wrong...')
