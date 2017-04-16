/* Code snippet for getting the words from the page: https://www.hackthissite.org/missions/prog/1/ */
var x = document.getElementsByClassName('sitebuffer')[0].getElementsByTagName('li');
var y = '';

// Comma separate every word
for (i of x)
    y += i.textContent + ',';

// Print words into the console
console.log(y.slice(0, -1));
