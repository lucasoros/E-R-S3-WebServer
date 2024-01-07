// const inputText = document.querySelector('input[type="text"]');

// inputText.addEventListener('keyup', function (event) {
//   if (event.key === 'Enter') {
//     const valeur = '4';

//     // Envoyer la valeur au microcontrôleur (remplacez l'URL appropriée)
//     fetch("/sendvolt?value=" + valeur) // Utiliser la méthode POST pour envoyer la valeur
//       .then(response => response.text())
//       .then(data => {
//         console.log(data); // Réponse du microcontrôleur
//       });

//     inputText.value = '';
//   }
// });

const inputText = document.querySelector('input[type="text"]');
inputText.addEventListener('keyup', function (event) {
  if (event.key === 'Enter') {
    const valeur = inputText.value;
    fetch("/sendvolt", {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: 'value=' + valeur,
    })
      .then(response => response.text())
      .then(data => {
        console.log(data); // Réponse du serveur
      });
  }
});

