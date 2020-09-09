importScripts('../bootstrap/js/jquery.min.js')
$(this).on('message', function () {
    while (true) {
        this.postMessage(1001);
        var date = new Date();
        var currentDate = null;
        do {
            currentDate = new Date();
        } while (currentDate - date < 26);
    }
});