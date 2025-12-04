// 本地 MQTT Broker（替代 mosquitto）
const aedes = require('aedes')();
const net = require('net');
const server = net.createServer(aedes.handle);

const PORT = 1883;

server.listen(PORT, () => {
  console.log(`MQTT broker started on port ${PORT}`);
});

// WebSocket Server，用来给网页推送数据
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });

console.log("WebSocket server started on port 8080");

// 当 ESP32 发布 MQTT 消息时触发
aedes.on('publish', (packet, client) => {
  if (packet.topic === 'esp32/data') {
    const msg = packet.payload.toString();
    console.log("ESP32 =>", msg);

    // 推给网页
    wss.clients.forEach(ws => ws.send(msg));
  }
});