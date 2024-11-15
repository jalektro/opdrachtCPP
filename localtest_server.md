let socket = new WebSocket("ws://localhost:1234");

socket.onopen = function() {
    console.log("Verbonden met server");
    socket.send("Test bericht");
};

socket.onmessage = function(event) {
    console.log("Antwoord van server:", event.data);
};

