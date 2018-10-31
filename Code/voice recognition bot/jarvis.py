from gtts import gTTS
import speech_recognition as sr
import os
import webbrowser

def TalktoMe(audio):
    print(audio)
    tts = gTTS(text = audio,lang = 'en')
    tts.save('audio.mp3')
    os.system('mpg123 audio.mp3')
    
def myCommand():
    r = sr.Recognizer()
    
    with sr.Microphone() as source:
        print("i am ready!")
        r.pause_threshold = 1
        r.adjust_for_ambiant_noise(source, durration =1)
        audio = r.listen(source)
    
    try:
        command = r.recognize_google(audio)
        #print("you said: "+ command +"\n")
        
    except sr.UnknownValueError:
        assistant(myCommand())
        
        return command
    
def assistant(command):
    
    print("Command is: "+ command)
    
    if 'open reddit python' in command:
        ffox_path = 'C:\Program Files\Mozilla Firefox\firefox.exe'
        url= 'https://www.reddit.com/python'
        webbrowser.get(ffox_path).open(url)
        
    if 'Hello' in command:
        TalktoMe('Hello')
        
    
        
TalktoMe("i am ready!")

while True:
    assistant(myCommand())