const express = require('express');
const axios = require('axios');

const app = express();
const port = 3000;

const arduinoIP = 'http://192.168.123.44'; // Replace with your Arduino's IP address

// Define an API endpoint
app.get('/on', async (req, res) => {
  try {
    const response = await axios.get(`${arduinoIP}/on`);
    res.json(response.data);
  } catch (error) {
    res.status(500).json({ error: 'Error fetching data from Arduino' });
  }
});

// Define an API endpoint
app.get('/off', async (req, res) => {
    try {
      const response = await axios.get(`${arduinoIP}/off`);
      res.json(response.data);
    } catch (error) {
      res.status(500).json({ error: 'Error fetching data from Arduino' });
    }
  });

// Start the server
app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}/`);
});
