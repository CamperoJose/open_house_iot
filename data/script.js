function obtenerFechaHora() {
    const ahora = new Date();
    const opciones = { year: 'numeric', month: 'long', day: 'numeric', hour: 'numeric', minute: 'numeric', second: 'numeric', hour12: false };
    return ahora.toLocaleDateString('es-ES', opciones);
}

function actualizarFechaHora() {
    const fechaHoraElemento = document.getElementById('fecha-hora');
    if (fechaHoraElemento) {
        fechaHoraElemento.textContent = obtenerFechaHora();
    }
}



//funciones de botones de las caras

function happy() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/happy", true);
    xhttp.send();
}

function sad() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/sad", true);
    xhttp.send();
}

function angry() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/angry", true);
    xhttp.send();
}

function neutral() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/neutral", true);
    xhttp.send();
}

function surprised() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/surprised", true);
    xhttp.send();
}

function laughing() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/laughing", true);
    xhttp.send();
}

function cool() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/cool", true);
    xhttp.send();
}

function nerd() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/nerd", true);
    xhttp.send();
}

function heart() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/heart", true);
    xhttp.send();
}

//fin funciones de botones de las caras



setInterval(actualizarFechaHora, 1000);

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("pulsador").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/pulsador", true);
    xhttp.send();
}, 1000);

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("RSSI").innerHTML = this.responseText;
        }

        if (document.getElementById("RSSI").innerHTML > -25) {
            document.getElementById("wifi").src = "assets/red1.png";
        } else if (document.getElementById("RSSI").innerHTML > -50) {
            document.getElementById("wifi").src = "assets/red2.png";
        } else if (document.getElementById("RSSI").innerHTML > -75) {
            document.getElementById("wifi").src = "assets/red3.png";
        } else {
            document.getElementById("wifi").src = "assets/red4.png";
        }
    };
    xhttp.open("GET", "/RSSI", true);
    xhttp.send();
}, 1000);

$(document).ready(function() {
    $('#imageCarousel').carousel();
    $('#imageCarousel').on('slid.bs.carousel', function() {
        var currentIndex = $('#imageCarousel .carousel-inner .carousel-item.active').index() + 1;
        $('#positionIndicator').text('Imagen ' + currentIndex);
    });
});