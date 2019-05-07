var socket = io();
var data = {};

socket.on('updateData',function(data){
  console.log("Update: ", data);
  /*
  socket.emit("getData");
  $('#tempData').text(data.temp);
  $('#humidData').text(data.humidity);
  */
});
