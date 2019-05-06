/**
 * A socket.io server that serves a static website and
 * sends events from the ESP8266 to the website
 */

// Import libraries
var express = require('express');
var http = require('http');
var socketio = require('socket.io');

// Initialize the server
var app = express();
var server = http.createServer(app);
var io = socketio(server);

app.use(express.static('/public'));

// Start the server on port 3000
server.listen(3000);


// Handle socket.io events
io.on('connection', socket => {
  socket.on('event-name', data => {
    // go
  })
})
