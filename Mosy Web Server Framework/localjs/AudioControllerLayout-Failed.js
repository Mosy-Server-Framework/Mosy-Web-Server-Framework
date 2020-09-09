function SclLi(index) {
    var ctop = parseInt($('#LyircUl').children().eq(index).offset().top);
    var ptop = parseInt($('#LyircUl').offset().top);
    var t = ctop - ptop - 268;
    $('li.LyircNormal.Forced').animate({ fontSize: '20px' }, 200);
    $('li.LyircNormal.Forced').removeClass('Forced');
    $('#LyircUl').children().eq(index).animate({ fontSize: '30px' }, 200);
    $('#LyircUl').children().eq(index).addClass('Forced');
    $('#LyircOverlay').animate({ scrollTop: t }, 200);
}
var currentIndex = 0;
var Paused = true;
var PanelHide = false;
var ListHide = true;
var TitleHide = false;
var ControlHide = true;
var Overlay = false;
//For js
/*
 * Message
 * +-Event
 * +-WParam
 * +-LParam
 */
function AddList(name) {
    var path = String(name);
    var index = path.lastIndexOf('\\');
    var n = path.substring(index + 1, path.length);
    $('#PlayList').append('<li class="ListItem"><a class="ListText">' + n + '</a></li>');
    MapList.push(name);
}
function Close() {
    window.CloseWnd();
}
function Minimsize() {
    window.MinimsizeWnd();
}
function LeftVolume(v) {
    window.SetLeftVolume(v);
}
function RightVolume(v) {
    window.SetRightVolume(v);
}
function LeftEchoVolume(v) {
    window.SetEchoLeftVolume(v);
}
function RightEchoVolume(v) {
    window.SetEchoRightVolume(v);
}
function GlobalVolume(v) {
    window.SetGlobalVolume(v);
}
function EchoLeft(v) {
    window.SetEchoLeft(v);
}
function EchoRight(v) {
    window.SetEchoRight(v);
}
function EchoLeftVolume(v) {
    window.SetEchoLeftVolume(v);
}
function EchoRightVolume(v) {
    window.SetEchoRightVolume(v);
}
function Tempo(v) {
    window.SetTempo(v);
}
function Speed(v) {
    window.SetSpeed(v)
}
function Rate(v) {
    window.SetRate(v);
}
function InsertFile() {
    var file = window.GetInsertFile();
    AddList(file);
}
function PosChange(v) {
    window.OnPosChange(v);
}
function QueryPause(p) {
    Paused = p;
    if (Paused) {
        $('#PlayBtn').attr('src', './bootstrap-icons/play.svg');
    }
    else {
        $('#PlayBtn').attr('src', './bootstrap-icons/pause.svg');
    }
}
function SubitPause() {
    window.SetPause(Paused);
}
function PlayFile(path, title) {
    window.LibPlayFile(path, title);
}
function LBtnDown() {
    window.SetLBtnDown();
}
function LBtnUp() {
    window.SetLBtnUp();
}
function PlayNext() {
    var path = GetNextPath();
    var title = GetCurrentName();
    $('#DialogTitle').text(title + ' - Audio Controller');
    $('#MusicTitle').text(title);
    PlayFile(path, title);
}
function PlayLast() {
    var path = GetLastPath();
    var title = GetCurrentName();
    $('#DialogTitle').text(title + ' - Audio Controller');
    $('#MusicTitle').text(title);
    PlayFile(path, title);
}
//For C++
function RequestLyircIndex() {
    return window.GetLyircIndex()
}
function RequestLeftRect() {
    return window.GetLeftRect();
}
function RequestRightRect() {
    return window.GetRightRect();
}
function RequestPos() {
    return window.RequestPosW();
}
function warn(title, text) {
    $('#DlgTitle').text(title);
    $('#DlgText').text(text);
    $('#ModalDlg').modal('show');
}
function AddLyric(l) {
    alert(l);
    $('#LyircUl').append('<li class="LyircNormal">' + l + '</li>');
}
function LoadLyirc() {
    var LArr = window.LoadLyirc();
    $('#LyircUl').empty();
    for (var i = 0; i < LArr.length(); i++) {
        $('#LyircUl').append('<li class="LyircNormal">' + LArr[i] + '</li>');
    }
}
function RefreshRect(RLArr, RRArr) {
    $("#RightRect").empty();
    $("#LeftRect").empty();
    for (var i = 0; i < Math.min(RLArr.lenght, RRArr.lenght); i++) {
        $("#RightRect").append('<li class="RectRight" style="width:' + RRArr[i] + 'px;margin-left:' + (240 - RRArr[i]) + '"></li>');
        $("#LeftRect").append('<li class="RectLeft" style="width:' + RLArr[i] + 'px"></li>');
    }
}
function LoadLeftRect(index, Data) {
    $('#LeftRect').children().eq(index).animate({ 'width': Data + 'px' }, 24);
}
function LoadRightRect(index, Data) {
    var t = 240 - Data;
    $('#RightRect').children().eq(index).css({ 'width': Data + 'px', 'margin-left': t + 'px' }, 24);
}
function GetNextPath() {
    if (currentIndex + 1 >= MapList.length) {
        currentIndex = 0;
        return MapList[0];
    }
    else {
        currentIndex++;
        return MapList[currentIndex];
    }
}
function GetLastPath() {
    if (currentIndex <= 0) {
        currentIndex = MapList.length - 1;
        return MapList[currentIndex];
    }
    else {
        currentIndex--;
        return MapList[currentIndex];
    }
}
function GetCurrentName() {
    var path = String(MapList[currentIndex]);
    var index = path.lastIndexOf('/');
    var n = path.substring(index + 1, path.length);
    return n;
}
function ItemClick(v) {
    //alert(MapList);
    $('li.ListItem.active').removeClass('active');
    $(v).addClass('active');
}
function ItemDbClick(v) {
    var index = $('li.ListItem').index(v);
    var p = MapList[index];
    currentIndex = index;
    var title = GetCurrentName();
    $('#DialogTitle').text(title + ' - Audio Controller');
    $('#MusicTitle').text(title);
    PlayFile(p, title);
}
function SelectFiles() {
    window.GetInsertFile();
}
function HideAllPanels() {
    //$("#MusicPanel").animate({ top: '123px' }, 400);
    $("#ListDiv").animate({ left: '-245px' }, 400);
    //$("#TitleBar").animate({ top: '-44px' });
    $("#ControlPanel").animate({ left: '245px' }, 400);
    if (Paused) {
        if (TitleHide) {
            $("#TitleBar").stop();
            $("#TitleBar").animate({ top: '0px' });
            TitleHide = false;
        }
        if (PanelHide) {
            $("#MusicPanel").stop();
            $("#MusicPanel").animate({ top: '0px' });
            PanelHide = false;
        }
    }
    //PanelHide = true;
    ListHide = true;
    //TitleHide = true;
    ControlHide = true;
}
Array.prototype.removeByValue = function (val) {
    for (var i = 0; i < this.length; i++) {
        if (this[i] == val) {
            this.splice(i, 1);
            break;
        }
    }
}
function SliderBg(d) {
    var w = $('#Slider').width();
    var max = $('#Slider').attr('max');
    var t = d * w / max;
    $('#Slider').css('background-size', parseInt(t) + 'px ' + $('#Slider').attr('max') + 'px');
}
var MapList = new Array();
function RemoveList() {
    var index = $('li.ListItem.active').index();
    $('li.ListItem.active').remove();
    MapList.splice(index, 1);
    if (index <= currentIndex) {
        if (currentIndex <= 0) {
            currentIndex = MapList.length - 1;
        }
        else {
            currentIndex--;
        }
    }
}
$('#MainPanel').keydown(function (event) {
    var e = event || window.event;
    var k = e.keyCode || e.which;
    switch (k) {
        case 37:
            $('#Value').val($('#Value').val() - 10);
            $('#Value').trigger('input');
            break;
        case 38:
            PlayLast();
            break;
        case 177:
            PlayLast();
            break;
        case 39:
            $('#Value').val($('#Value').val() + 10);
            $('#Value').trigger('input');
            break;
        case 40:
            PlayNext();
            break;
        case 176:
            PlayNext();
            break;
        case 32:
            $('#PlayBtn').click();
            if (Paused) {
                $(this).attr('src', './bootstrap-icons/play.svg');
            }
            else {
                $(this).attr('src', './bootstrap-icons/pause.svg');
            }
            break;
        case 179:
            $('#PlayBtn').click();
            if (Paused) {
                $(this).attr('src', './bootstrap-icons/play.svg');
            }
            else {
                $(this).attr('src', './bootstrap-icons/pause.svg');
            }
            break;
        case 178:
            if (!Paused) {
                $('#PlayBtn').click();
                $(this).attr('src', './bootstrap-icons/play.svg');
            }
            break;
    }
    return false;
});
var oScirpt;
function cb(data) {
    $('body').find('script').remove();
    console.log(data);
    $('#ResultList').empty();
    if(data.result) {
        var so = data.result.songs;

        for (var i = 0; i < so.length; i++) {
            var l1 = so[i].name;
            var l='';
            console.log(so[i]);
            for (var j = 0; j < so[i].artists.length; j++) {
                l += so[i].artists[j].name;
                l += ';';
            }
            $('#ResultList').append('<tr><td>' + l1 + '</td><td>' + l + '</td><td><button class="btn btn-kali btn-oplay" style="float:right;display:inline;margin-left:2px;margin-right:2px">Download And Play</button></td></tr>');
        }
        Overlay = true;
        $('#SearchResult').show();
        $("#MusicPanel").stop();
        $("#MusicPanel").animate({top: '123px'}, 400);
    }
    PanelHide = false;
}
$(document).ready(function () {
    var first = true;
    function PrefixInteger(num, len) {
        return (Array(len).join('0') + num).slice(-len);
    }
    $("#RightRect").empty();
    $("#LeftRect").empty();
    for (var i = 0; i < 27; i++) {
        $("#RightRect").append('<li class="RectRight" style="width:0px;margin-left:240px"></li>');
        $("#LeftRect").append('<li class="RectLeft" style="width:0px"></li>');
    }
    $("#ListDiv").animate({ left: '-245px' }, 400);
    //$("#TitleBar").animate({ top: '-44px' });
    $("#ControlPanel").animate({ left: '245px' }, 400);
    $("#Value").css('background-size', '100% 100%');
    $("#Speed").css('background-size', '50% 100%');
    $("#Rate").css('background-size', '50% 100%');
    $("#Tempo").css('background-size', '50% 100%');
    $(document).mousemove(function (e) {
        OnPage = true;
        if (e.pageY <= 40 && !(e.pageX <= 240 && !ListHide) && !(e.pageX >= 734 && !ControlHide)) {
            if (TitleHide) {
                $("#TitleBar").stop();
                $("#TitleBar").animate({ top: '0px' });
                TitleHide = false;
            }
        }
        if (e.pageY > 40 && !Paused) {
            if (!TitleHide&&!Overlay) {
                $("#TitleBar").stop();
                $("#TitleBar").animate({ top: '-44px' });
                TitleHide = true;
            }
        }
        if (e.pageY >= 460 && !(e.pageX <= 240 && !ListHide) && !(e.pageX >= 734 && !ControlHide)) {
            if (PanelHide&&!Overlay) {
                $("#MusicPanel").stop();
                $("#MusicPanel").animate({ top: '0px' });
                PanelHide = false;
            }
        }
        if (e.pageY < 430 && !Paused) {
            if (!PanelHide) {
                $("#MusicPanel").stop();
                $("#MusicPanel").animate({ top: '123px' }, 400);
                PanelHide = true;
            }
        }
        if (e.pageX <= 40) {
            if (ListHide&&!Overlay) {
                if (Paused) {
                    if (!TitleHide) {
                        $("#TitleBar").stop();
                        $("#TitleBar").animate({ top: '-44px' });
                        TitleHide = true;
                    }
                    if (!PanelHide) {
                        $("#MusicPanel").stop();
                        $("#MusicPanel").animate({ top: '123px' }, 400);
                        PanelHide = true;
                    }
                }
                $("#ListDiv").stop();
                $("#ListDiv").animate({ left: '0px' }, 400);
                ListHide = false;
            }
        }
        if (e.pageX > 240) {
            if (!ListHide) {
                if (Paused) {
                    if (TitleHide) {
                        $("#TitleBar").stop();
                        $("#TitleBar").animate({ top: '0px' });
                        TitleHide = false;
                    }
                    if (PanelHide) {
                        $("#MusicPanel").stop();
                        $("#MusicPanel").animate({ top: '0px' });
                        PanelHide = false;
                    }
                }
                $("#ListDiv").stop();
                $("#ListDiv").animate({ left: '-245px' }, 400);
                ListHide = true;
            }
        }
        if (e.pageX >= 914) {
            if (ControlHide&&!Overlay) {
                if (Paused) {
                    if (!TitleHide) {
                        $("#TitleBar").stop();
                        $("#TitleBar").animate({ top: '-44px' });
                        TitleHide = true;
                    }
                    if (!PanelHide) {
                        $("#MusicPanel").stop();
                        $("#MusicPanel").animate({ top: '123px' }, 400);
                        PanelHide = true;
                    }
                }
                $("#ControlPanel").stop();
                $("#ControlPanel").animate({ left: '0px' }, 400);
                ControlHide = false;
            }
        }
        if (e.pageX < 714) {
            if (!ControlHide) {
                if (Paused) {
                    if (TitleHide) {
                        $("#TitleBar").stop();
                        $("#TitleBar").animate({ top: '0px' });
                        TitleHide = false;
                    }
                    if (PanelHide) {
                        $("#MusicPanel").stop();
                        $("#MusicPanel").animate({ top: '0px' });
                        PanelHide = false;
                    }
                }
                $("#ControlPanel").stop();
                $("#ControlPanel").animate({ left: '245px' }, 400);
                ControlHide = true;
            }
        }
    });
    $("input.ne-range").on("input", function () {
        var min;
        var max;
        var step;
        min = $(this).attr('min');
        max = $(this).attr('max');
        step = $(this).attr('step');
        $(this).css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
        if (this.id == 'Slider') {
            var sec = PrefixInteger(this.value % 60, 2);
            var v = parseInt(this.value / 60);
            var min = PrefixInteger(v % 60, 2);
            v = parseInt(v / 60);
            var hour = PrefixInteger(v % 60, 2);
            $("#CurrentTime").text(hour + ":" + min + ":" + sec);
            PosChange(this.value);
        }
        else if (this.id == 'GlobalVolume') {
            var Id = $(this).attr('id');
            Id += "V";
            $("#" + Id).text(this.value);
            $('#Value').val(this.value);
            $('#Value').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            $('#LeftVolume').val(this.value);
            $("#LeftVolumeV").text(this.value);
            $('#LeftVolume').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            $('#RightVolume').val(this.value);
            $("#RightVolumeV").text(this.value);
            $('#RightVolume').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            GlobalVolume(this.value);
        }
        else if (this.id == 'Value') {
            $('#GlobalVolume').val(this.value);
            $("#GlobalVolumeV").text(this.value);
            $('#GlobalVolume').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            $('#LeftVolume').val(this.value);
            $("#LeftVolumeV").text(this.value);
            $('#LeftVolume').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            $('#RightVolume').val(this.value);
            $("#RightVolumeV").text(this.value);
            $('#RightVolume').css('background-size', (this.value - min) * 100.0 / (max - min) + '% 100%');
            GlobalVolume(this.value);
        } else {
            var Id = $(this).attr('id');
            Id += "V";
            $("#" + Id).text(this.value);
            if (this.id == 'LeftVolume') {
                LeftVolume(this.value);
            }
            if (this.id == 'RightVolume') {
                RightVolume(this.value);
            }
            if (this.id == 'Rate') {
                Rate(this.value);
                var Id = $(this).attr('id');
                Id += "V";
                $("#" + Id).text(this.value - 100);
            }
            if (this.id == 'Speed') {
                Speed(this.value);
                var Id = $(this).attr('id');
                Id += "V";
                $("#" + Id).text(this.value - 100);
            }
            if (this.id == 'Tempo') {
                Tempo(this.value);
                var Id = $(this).attr('id');
                Id += "V";
                $("#" + Id).text(this.value - 100);
            }
            if (this.id == 'LeftTime') {
                EchoLeft(this.value);
            }
            if (this.id == 'RightTime') {
                EchoRight(this.value);
            }
            if (this.id == 'LeftEchoVolume') {
                LeftEchoVolume(this.value);
            }
            if (this.id == 'RightEchoVolume') {
                RightEchoVolume(this.value);
            }
        }
    });
    function HideMusicPanel() {
        if (!PanelHide) {
            $("#MusicPanel").stop();
            $("#MusicPanel").animate({ top: '123px' }, 400);
            PanelHide = true;
        }
    };
    $('li.ListItem').click(function () {
        alert(1);
        $('li.ListItem.active').removeClass('active');
        $(this).addClass('active');
    });
    $('li.ListText').click(function () {
        alert(1);
        $('li.ListItem.active').removeClass('active');
        $(this).parent.addClass('active');
    });
    $('#ResetTempo').click(function () {
        $("#Speed").val(100);
        $("#Rate").val(100);
        $("#Tempo").val(100);
        $("#Speed").css('background-size', '50% 100%');
        $("#Rate").css('background-size', '50% 100%');
        $("#Tempo").css('background-size', '50% 100%');
        $("#SpeedV").text('0');
        $("#RateV").text('0');
        $("#TempoV").text('0');
        $("#Speed").trigger('input');
        $("#Rate").trigger('input');
        $("#Tempo").trigger('input');
    });
    $('#ResetEcho').click(function () {
        $("#LeftTime").val(0);
        $("#RightTime").val(0);
        $("#LeftEchoVolume").val(0);
        $("#RightEchoVolume").val(0);
        $("#LeftTime").css('background-size', '0% 100%');
        $("#RightTime").css('background-size', '0% 100%');
        $("#LeftEchoVolume").css('background-size', '0% 100%');
        $("#RightEchoVolume").css('background-size', '0% 100%');
        $("#LeftTimeV").text('0');
        $("#RightTimeV").text('0');
        $("#LeftEchoVolumeV").text('0');
        $("#RightEchoVolumeV").text('0');
        $("#LeftTime").trigger('input');
        $("#RightTime").trigger('input');
        $("#LeftEchoVolume").trigger('input');
        $("#RightEchoVolume").trigger('input');
    });
    $('#PlayBtn').mouseover(function () {
        if (Paused) {
            $(this).attr('src', './bootstrap-icons/play-fill.svg');
        }
        else {
            $(this).attr('src', './bootstrap-icons/pause-fill.svg');
        }
    });
    $('#PlayBtn').mouseout(function () {
        if (Paused) {
            $(this).attr('src', './bootstrap-icons/play.svg');
        }
        else {
            $(this).attr('src', './bootstrap-icons/pause.svg');
        }
    });
    $('#PlayBtn').click(function () {
        Paused = !Paused
        if (Paused) {
            SubitPause();
            $(this).attr('src', './bootstrap-icons/play.svg');
            if (TitleHide) {
                $("#TitleBar").stop();
                $("#TitleBar").animate({ top: '0px' });
                TitleHide = false;
            }
            if (PanelHide) {
                $("#MusicPanel").stop();
                $("#MusicPanel").animate({ top: '0px' });
                PanelHide = false;
            }
        }
        else {
            SubitPause();
            $(this).attr('src', './bootstrap-icons/pause.svg');
            if (!TitleHide) {
                $("#TitleBar").stop();
                $("#TitleBar").animate({ top: '-44px' });
                TitleHide = true;
            }
        }
    });
    $('#SubSearch').click(function () {
        oScirpt = document.createElement('script');
        console.log($('#Keyword').val());
        oScirpt.src = 'http://s.music.163.com/search/get/?type=1&filterDj=true&s=\"'+$('#Keyword').val()+'\"&limit=100&offset=0&callback=cb';
        document.body.appendChild(oScirpt);
    });
    $('#SubSearch2').click(function () {
        oScirpt = document.createElement('script');
        console.log($('#Keyword2').val());
        oScirpt.src = 'http://s.music.163.com/search/get/?type=1&filterDj=true&s=\"'+$('#Keyword2').val()+'\"&limit=100&offset=0&callback=cb';
        document.body.appendChild(oScirpt);
    });
});
