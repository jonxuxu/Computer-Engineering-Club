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

// Serve the static website
app.use(express.static('public'));

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

// Handle socket.io events
io.on('connection', socket => {
  console.log('User connected: ' + socket.id);
  socket.on('disconnect', function(){
    console.log('User disconnected: ' + socket.id);
  });
  socket.on('updateData', data => {
    console.log("New data: " + data);
    socket.broadcast.emit('updateData', data);
  });
});

// Start the server on port 3000
server.listen(3000);
console.log('Server started on port 3000')
