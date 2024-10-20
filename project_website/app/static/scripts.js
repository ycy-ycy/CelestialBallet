let bodyCount = 0;

// Function to add a new celestial body form
function addCelestialBodyForm() {
  bodyCount += 1;

  const bodyForm = `
    <div class="bodyForm" id="body${bodyCount}">
      <h3>Celestial Body ${bodyCount}</h3>
      <label for="bodyType${bodyCount}">Choose a Celestial Body:</label>
      <select id="bodyType${bodyCount}" name="bodyType">
        <option value="planet">Planet</option>
        <option value="star">Star</option>
      </select><br><br>

      <label for="x${bodyCount}">Position X:</label>
      <input type="number" id="x${bodyCount}" name="x" step="any" required><br><br>

      <label for="y${bodyCount}">Position Y:</label>
      <input type="number" id="y${bodyCount}" name="y" step="any" required><br><br>

      <label for="z${bodyCount}">Position Z:</label>
      <input type="number" id="z${bodyCount}" name="z" step="any" required><br><br>

      <label for="mass${bodyCount}">Mass:</label>
      <input type="number" id="mass${bodyCount}" name="mass" step="any" required><br><br>

      <label for="radius${bodyCount}">Radius:</label>
      <input type="number" id="radius${bodyCount}" name="radius" step="any" required><br><br>

      <label for="rotationSpeed${bodyCount}">Rotation Angular Speed:</label>
      <input type="number" id="rotationSpeed${bodyCount}" name="rotationSpeed" step="any" required><br><br>

      <label for="theta${bodyCount}">Rotation Axis Theta:</label>
      <input type="number" id="theta${bodyCount}" name="theta" step="any" required><br><br>

      <label for="phi${bodyCount}">Rotation Axis Phi:</label>
      <input type="number" id="phi${bodyCount}" name="phi" step="any" required><br><br>
    </div>
  `;

  document.getElementById('bodiesContainer').insertAdjacentHTML('beforeend', bodyForm);
}

// Handle form submission
document.getElementById('inputForm').addEventListener('submit', function(event) {
  event.preventDefault();

  const bodies = [];

  // Loop through all the celestial body forms and collect the data
  for (let i = 1; i <= bodyCount; i++) {
    const bodyType = document.getElementById(`bodyType${i}`).value;
    const x = document.getElementById(`x${i}`).value;
    const y = document.getElementById(`y${i}`).value;
    const z = document.getElementById(`z${i}`).value;
    const mass = document.getElementById(`mass${i}`).value;
    const radius = document.getElementById(`radius${i}`).value;
    const rotationSpeed = document.getElementById(`rotationSpeed${i}`).value;
    const theta = document.getElementById(`theta${i}`).value;
    const phi = document.getElementById(`phi${i}`).value;

    bodies.push({
      bodyType, x, y, z, mass, radius, rotationSpeed, theta, phi
    });
  }

  fetch('/submit', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({ bodies })  // Send the data to the server
  })
  .then(response => response.text())
  .then(data => {
    const pixelData = data.split('\n');
    renderImage(pixelData);
  })
  .catch(error => console.error('Error:', error));
});

// Add a new celestial body form when the button is clicked
document.getElementById('addBodyBtn').addEventListener('click', addCelestialBodyForm);

// Function to render the image from the pixel data
function renderImage(pixelData) {
  const canvas = document.getElementById('resultCanvas');
  const ctx = canvas.getContext('2d');
  
  const width = 100; // Assume a 100x100 image for now
  const height = 100;
  canvas.width = width;
  canvas.height = height;

  const imageData = ctx.createImageData(width, height);

  for (let i = 0; i < pixelData.length; i++) {
    const [r, g, b] = pixelData[i].split(' ').map(Number);
    const index = i * 4;

    imageData.data[index] = r;     // Red
    imageData.data[index + 1] = g; // Green
    imageData.data[index + 2] = b; // Blue
    imageData.data[index + 3] = 255; // Alpha (fully opaque)
  }

  ctx.putImageData(imageData, 0, 0);
}