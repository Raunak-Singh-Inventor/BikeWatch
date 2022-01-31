import os
from playsound import playsound

while True:
    output = os.popen('./personDetection').read()
    print(output)
    if output=="1":
        print("person detected")
        playsound("text.mp3")
    else:
        print("no person")