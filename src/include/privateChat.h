#ifndef PRIVATE_CHAT_H
#define PRIVATE_CHAT_H
const char private_chat_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <title>Private Chat</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>

    <body>
        <nav class="title-bar"><span id="title">PRIVATE CHAT:</span></nav>
        <div id="chat-display">
            <div id="message-container"></div>
            <div class="chat-bar">
                <div id="form">
                    <form>
                        <input type="text" name="chatMessage" id="chatMessage" placeholder="Your Message"></input>
                        <button type="button" id="sendBtn" class="sendBtn">Send</button>
                        <p id="makeshiftErrorOutput" class="hidden"></p>
                    </form>
                </div>
            </div>
        </div>

        <script>
            var sduid = "you";
            const username = sessionStorage.getItem("username");

             function displayNewMessage(newMessage, sent){
                var card = document.createElement("div");
                if(sent){
                    card.classList.add("sent-message-card");
                }else{
                    card.classList.add("received-message-card");
                }
                card.innerHTML = newMessage.message.body + '</p><span class="duid">FROM DUCKID: '
                 + newMessage.sduid + '</span></p><span class="name">' 
                 + newMessage.message.username + '</span>';

                document.getElementById('message-container').append(card);
            }
            function chatHistoryListener () {
                var data = JSON.parse(this.responseText);
                data.posts.forEach(item => {
                        let sent = sduid == item.sduid ? true : false;
                        displayNewMessage(item, sent);
                    });
                //document.getElementById('dduid').innerHtml = "PRIVATE CHAT: " + ;
                
            }

            function sduidListener(){
                sduid = this.responseText;
            }
            function requestSduid(){
                var req = new XMLHttpRequest();
                req.addEventListener("load", sduidListener);
                req.addEventListener("error", errorListener);
                req.open("GET", "/id");
                req.send();
            }

            function requestChatHistory(){
                var req = new XMLHttpRequest();
                req.addEventListener("load", chatHistoryListener);
                req.addEventListener("error", errorListener);
                req.open("GET", "/privateChatHistory");
                req.send();
            }


            function loadListener(){
                var errEl = document.getElementById('makeshiftErrorOutput');
                if (!errEl.classList.toString().includes("hidden")) {
                    errEl.innerHTML = '';
                    errEl.classList.add("hidden");
                }
            };
            function errorListener(){
                var errorMessage = 'There was an error sending the message. Please try again.';
                console.log(errorMessage);
                var errEl = document.getElementById('makeshiftErrorOutput');
                errEl.innerHTML = errorMessage;
                errEl.classList.remove("hidden");
            };
            function sendMessage(){
                let messageBody = document.getElementById('chatMessage').value;
                let message = JSON.stringify({
                    body: messageBody,
                    username: username
                });
                let messageParams = new URLSearchParams("");
                messageParams.append("chatMessage", message);
                var req = new XMLHttpRequest();
                req.addEventListener("load", loadListener);
                req.addEventListener("error", errorListener);
                req.open("POST", "/privateChatSubmit.json?" + messageParams.toString());
                req.send();
                displayNewMessage({message: { body: messageBody, username: username} , sduid: sduid}, true);

                document.getElementById('chatMessage').value = "";
            }
            
            if (!!window.EventSource) {
                var source = new EventSource('/events');

                source.addEventListener('open', function(e) {
                    console.log("Events Connected");
                }, false);

                source.addEventListener('error', function(e) {
                    if (e.target.readyState != EventSource.OPEN) {
                    }
                }, false);
                source.addEventListener('refreshPage', function(data) {
                    location.reload(); 
                }, false);

            }
            document.getElementById('sendBtn').addEventListener('click', sendMessage);
            
            requestSduid();
            requestChatHistory();
            document.getElementById("chatMessage").focus();
        </script>
    </body>
</html>


<style>
    .received-message-card{
        border-radius: 10px;
        background-color: #F0EEF7;
        padding: 5px 3vw 1vh;
        margin: 2vw;
        overflow:auto;
        width: 70%;
    }
    .sent-message-card{
        border-radius: 10px;
        background-color: #ffff004f;
        padding: 5px 3vw 1vh;
        margin: 2vw;
        overflow:auto;
        width: 70%;
        float: right;
    }
    #message-container{
        width: 95%;
        margin: 10vh auto;
    }
    .name{
        margin-right: 3vw;
        float: right;
        color: gray;
        font-size: 0.8em;
    }
    .duid{
        margin-left: 3vw;
        float: left;
        color: gray;
        font-size: 0.8em;
    }
    #title{
        font-size: 1.2em;
        top: 20%;
        position: relative;
        font-weight: bold;
    }
    .title-bar{
        background-color: black;
        box-shadow: 0 2px 3px gray;
        height: 35px;
        position: fixed;
        top: 0%;
        width: 100%;
        color: white;
        left: 0%;
        text-align: center;
    }
    .chat-bar{
        background-color: #9b9389;
        height: 35px;
        position: fixed;
        bottom: 0;
        width: 100%;
        padding: 5px;
        left: 0%;
    }
    #chatMessage{
        width: 70%;
    }
    #sendBtn{
        background-color: #ffe700;
        border-radius: 5px;
        border-style: none;
        height: 34px;
        width: 100px;
        float: right;
        margin-right: 15px;
    }
    body{
        font-family: sans-serif;
        font-size: .9em;
    }

</style>
)=====";
#endif