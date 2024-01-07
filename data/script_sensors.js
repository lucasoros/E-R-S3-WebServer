function updatePotValue() {
    fetch('/POT_val') // Request the potentiometer value
      .then(response => response.text())
      .then(value => {
        document.getElementById('potValue').textContent = 'Potentiometer Value: ' + value;
      });
  }
  // Update the potentiometer value every 1000 milliseconds (1 second)
  setInterval(updatePotValue, 1000);