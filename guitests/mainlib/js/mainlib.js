

function main_motor_click(el, header, ron){
    var target=el;
    if (!target) return;
    if (el.getAttribute('disable')=='true') return;
    
    if (!el.getAttribute('id')) return;
    
    if (el.popup) {
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
        return;
    }
    
    if (el.getAttribute('cursor')!='pointer') return;
    
    
    
    var documentElement = document.documentElement;
    
    var htmlns="http://www.w3.org/1999/xhtml";
    var svgns="http://www.w3.org/2000/svg";
    
    
    
    var x=parseFloat(target.getAttribute('x'));
    var y=parseFloat(target.getAttribute('y'));
    var width=parseFloat(target.getAttribute('width'));
    var height=parseFloat(target.getAttribute('height'));
    
    var cx=x+width / 2;
    var cy=y+height / 2;
    
    var viewwidth = 150;
    var viewheight = 150;
    
    var vx= cx - viewwidth / 2;
    var vy= y;
    var vheight= height + viewheight;
    var vwidth = viewwidth;
    
    
    var svg = mainlibutil.svg.create_svg(documentElement, 
        vx, vy ,  vheight , vwidth);
        
    svg.setAttribute('opacity', '0.8');     

    el.popup=svg;

    var g = mainlibutil.svg.create_rect(svg,
        0,  0,  vheight,  vwidth,  0, 0,
        'fill: transparent; stroke-width: 0; cursor: pointer;' );
    
   
    var svgm = mainlibutil.svg.create_svg( svg,
        0,  height, vheight-height, vwidth,  
        '0 0 1000 1000');
    
    var gw = document.createElementNS(svgns, 'g');
    svgm.appendChild(gw);
    
    var rect = mainlibutil.svg.create_rect( gw,
        10, 10,  980, 980, 30, 30,
        'fill: #F0F0F0; stroke-width: 0; ');
    
     
    rect.onmouseout = function() {
        event.preventDefault();
        event.stopPropagation();
        return;
    }       
    

    var headerrect= mainlibutil.svg.create_header(gw,
        50,50,400,900, 10, 10,
        'fill: #000033; stroke: yellow; stroke-with: 10; cursor: default;',
        header,
        'background: transparent; color: yellow; '+
        'text-align: center; vertical-align: middle;' +
        'font-family: sans-serif; font-size: 80px; height: 400px; ;');
        

    
    var btnoffrect=mainlibutil.svg.create_button(gw,
        100,  500,  400,  800,  60,  60,
        'cursor: pointer; stroke: red; stroke-width: 0', "redgradh",
        'Стоп', 'font-size: 120; fill: white; cursor: pointer;');
                                                 
    
    btnoffrect.setAttribute( 'display',"#{ ("+ron+") ? 'block' : 'none'}");
    btnoffrect.onclick=function(){
        dvnci_exec(ron+' @ 0');
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
    }
    
     btnoffrect.onmouseover = function (){
        btnoffrect.setAttribute('style', 'cursor: pointer; stroke: yellow; ');
    }
    
    

    
    var btnonrect=mainlibutil.svg.create_button(gw,
        100,  500,  400,  800,  60,  60,
        'cursor: pointer; stroke: green; stroke-width: 0', "greengradh",
        'Пуск', 'font-size: 120; fill: white; cursor: pointer;');
                                                 
    btnonrect.setAttribute( 'display',"#{ (!"+ron+") ? 'block' : 'none'}");
    btnonrect.onclick=function(){
        dvnci_exec(ron+' @ 1');
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
    }
    
     btnonrect.onmouseover = function (){
        btnonrect.setAttribute('style', 'cursor: pointer; stroke: yellow;');
    }
    
    
    
    svg.onmouseout = function() {
        var trgt=event.target;
        if ((event.toElement!=g) && (event.toElement!=svgm) && (event.toElement!=gw) && (event.toElement!=rect) && (event.toElement!=headerrect)){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        };
    
}}
    
//gw.appendChild(btnonrect);
    
function main_label_click(nm){
      var tgnm=nm;
      var idtgnm=nm + '_divelem';
      var newwin = open('', event.target , "toolbar=0,location=0,left=400,top=200, width=650,height=250");
      newwin.document.open();    
      newwin.document.write('<?xml version="1.0" encoding="UTF-8"?>');
      newwin.document.write('   <html>');
      newwin.document.write('      <head>');
      newwin.document.write('<script type="text/javascript" src="../mainlib/js_ext/hightchart/jquery.min.js"></script>');
      newwin.document.write('<script type="text/javascript" src="../mainlib/js_ext/hightchart/highcharts.js"></script>');
      newwin.document.write('<script type="text/javascript" src="../mainlib/js_ext/hightchart/exporting.js"></script>');
      newwin.document.write('<script type="text/javascript" src="../mainlib/js/hightrend.js"></script>');
      newwin.document.write('<script type="text/javascript">');
            
      newwin.document.write('      function initform() {');
      newwin.document.write('      registratetrend("');
      newwin.document.write(idtgnm);
      newwin.document.write('", "');
      newwin.document.write(tgnm);
      newwin.document.write('");}');
		                                     
      newwin.document.write('</script>');
      newwin.document.write('</head>');
      newwin.document.write('<body style="width: 100%; height: 100%; margin: 0 0; padding 0 0;" onload="initform()">');
      newwin.document.write('        <div id="');
      newwin.document.write(idtgnm);
      newwin.document.write('" style="width: 100%; height: 100%; margin: 0 0; padding 0 0;"></div>');
      newwin.document.write('</body>');
      newwin.document.write('</html>');
      newwin.document.close();}
    
//documentElement.appendChild(svg);
    
    
    
    


