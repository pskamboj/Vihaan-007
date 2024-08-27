import cv2
import numpy as np
import urllib.request
import pyttsx3

def text_to_speech(helper,text):
    engine = pyttsx3.init()
    
    engine.setProperty('rate', 150)  
    engine.setProperty('volume', 0.9)  
    engine.say(helper)
    engine.say(text)

    engine.runAndWait()

url='http://192.168.29.86/cam-mid.jpg'
confThreshold=0.5
nmsThreshold=0.5
# cap = cv2.VideoCapture(0)
whT=320

classesFile='coco.names'
classNames=[]

with open(classesFile,'rt') as f:
    classNames = f.read().rstrip('\n').split('\n')

modelConfiguration= 'yolov3.cfg'
modelWeights='yolov3.weights'

net=cv2.dnn.readNetFromDarknet(modelConfiguration,modelWeights)
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)

def findobjects(output_list,img):
    hT,wT,cT=img.shape
    bbox=[]
    classIds=[]
    confs=[]

    for output in output_list:
        for detection in output:
            scores=detection[5:]
            classID=np.argmax(scores)
            confidence=scores[classID]
            if confidence>confThreshold:
                w,h=int(detection[2]*wT),int(detection[3]*hT)
                x,y=int((detection[0]*wT)-w/2),int((detection[1]*hT)-h/2)
                bbox.append([x,y,w,h])
                classIds.append(classID)
                confs.append(float(confidence))
    # print(len(bbox))
    indices=cv2.dnn.NMSBoxes(bbox,confs,confThreshold,nmsThreshold)

    for i in indices:
        i=i
        box=bbox[i]
        x,y,w,h=box[0],box[1],box[2],box[3]
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,255),2)
        name=f'{classNames[classIds[i]].upper()}'
        text_to_speech("there is a" ,name)
        print(name)
        # cv2.putText(img,f'{classNames[classIds[i]].upper()} {int(confs[i]*100)}%',(x,y-10),cv2.FONT_HERSHEY_SIMPLEX,0.6,(255,0,255),2)




while True:
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    img = cv2.imdecode(imgnp,-1)
    # success,img=im.read()

    blob = cv2.dnn.blobFromImage(img,1/255,(whT,whT),[0,0,0],1,crop=False)
    net.setInput(blob)

    layerNames=net.getLayerNames()
    net.getUnconnectedOutLayers()
    # print(net.getUnconnectedOutLayers())
    outputNames = [layerNames[i-1]for i in net.getUnconnectedOutLayers()]
    outputs=net.forward(outputNames)
    output_list=list(outputs)
    # print(output_list[0].shape)
    # print(output_list[1].shape)
    # print(output_list[2].shape)
    # print(output_list[0][0])

    findobjects(output_list,img)


    cv2.imshow('Image',img)
    key = cv2.waitKey(5)
    
    # Check if the pressed key is the Esc key (27 is the ASCII code for Esc)
    if key == 27:
        break  # Break out of the loop if the Esc key is pressed

# Close the window
cv2.destroyAllWindows()