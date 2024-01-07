document.getElementById('loginButton').addEventListener('click', function() {
    var name = document.getElementById('Name').value;
    var password = document.getElementById('Password').value;

    if (name === 'Lucas' && password === 'Balise') {
        window.location.href = '/home';
    } else {
        alert('Wrong name or password');
    }
});
