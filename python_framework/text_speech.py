import requests
from bs4 import BeautifulSoup
from gtts import gTTS
import os
from flask import Flask, request

app = Flask(__name__)
url="http://192.168.29.16"

def text_to_speech(url):
    # Fetch webpage content
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')

    # Extract text content from webpage
    text_content = ""
    for paragraph in soup.find_all('p'):
        text_content += paragraph.text.strip() + " "

    # Convert text to speech
    tts = gTTS(text_content, lang='en')

    # Save the speech as an mp3 file
    tts.save("output.mp3")

    # Play the speech
    os.system("start output.mp3")

@app.route('/generate_speech', methods=['POST'])
def generate_speech():
    data = request.get_json()
    url = data['url']
    text_to_speech(url)
    return "Speech generated successfully"

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
