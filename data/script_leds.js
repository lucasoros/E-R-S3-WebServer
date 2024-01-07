let val = 0;

document.getElementById('REDLED').addEventListener('click', function () {
  if (val == 0) {
    fetch("/LEDon")
      .then(response => response.text())
    val = 1;
  }
  else if (val == 1) {
    fetch("/LEDoff")
      .then(response => response.text())
    val = 0;
  }
});





let isMouseDown = false;

document.getElementById('RED-LED').addEventListener('mousedown', function () {
  isMouseDown = true;
  fetch("/LEDon")
    .then(response => response.text())
    .then(data => {
      console.log(data);
    })
});

document.getElementById('RED-LED').addEventListener('mouseup', function () {
  isMouseDown = false;
  fetch("/LEDoff")
    .then(response => response.text())
    .then(data => {
      console.log(data);
    })
});




let val_RGB = 0;

document.getElementById('RGB').addEventListener('click', function () {
  if (val_RGB == 0) {
    fetch("/LED_R")
      .then(response => response.text())
      val_RGB = 1;
  }
  else if (val_RGB == 1) {
    fetch("/LED_G")
      .then(response => response.text())
      val_RGB = 2;
  }
  else if (val_RGB == 2) {
    fetch("/LED_B")
      .then(response => response.text())
      val_RGB = 0;
  }
});