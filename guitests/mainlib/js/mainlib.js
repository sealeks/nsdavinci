var mainlib = {    
    
};

mainlib.element = {};


mainlib.element.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS('http://dvnci/mlib', name);
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlib.element.create_button = function (parent, id, caption, x , y, width, height){
    if (!parent) return;
    var newel = mainlib.element.create('button', parent);
    if (!newel) return;
    if (id) newel.setAttribute('id', id);
    if (caption) newel.setAttribute('caption', caption);
    if (x) newel.setAttribute('x', x);
    if (y) newel.setAttribute('y', y);
    if (width) newel.setAttribute('width', width);
    if (height) newel.setAttribute('height', height);
    if (parent) parent.appendChild(newel);
    return newel;
}


mainlib.armatura_popupbody  = function(el){
if (el.popup){
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
        return;
    }

    el.popup = mainlibutil.popup.createsvgs(el,200,200,0, null, 'fill: green; opacity: 0.5;');

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        };
    }
    
    el.popup.onmouseout = function(ev){
         
          if (!mainlibutil.dom.check_is_parent (el.popup,ev.toElement,true)){
              ///el.popup.parentNode.removeChild(el.popup);
              // el.popup=undefined;
          }};  
      
    return el.popup.popupbody;  
}


mainlib.armatura_popup_content =  function(id, el, header, type, on, off, rron, rroff, auto, rauto){
    var on_btn_caption = (type=='motor' ? 'Пуск' : 'Открыть');
    var off_btn_caption = (type=='motor' ? 'Стоп' : 'Закрыть');
    var stop_btn_caption = (type=='motor' ? 'Сброс' : 'Стоп');   
    var off_btn_color1='#800';
    var off_btn_color2='#B00';
    var on_btn_color1='#080';
    var on_btn_color2='#0B0';
    var stop_btn_color1='#880';
    var stop_btn_color2='#BB0';
    //ron = mainlibutil.util.trim(ron);
    //roff = mainlibutil.util.trim(roff);
    
    var headerrect= mainlibutil.svg.create_header(el,
        10,10,80,180, 5, 5,
        'fill: #333; stroke: white; stroke-with: 1; cursor: default;',
        header,
        'background: transparent; color: white; '+
        'text-align: center; vertical-align: middle;' +
        'font-family: sans-serif; font-size: 14px;');
    
    var typepopup = ((rron!='') && (rroff!='')) ? 2 : ((rron!='') ? 0 : 1);
    
    switch(typepopup){
        case 0:
        case 1:{         
            var btn = mainlib.element.create_button(el, id + '_onoffbutton', typepopup==0 ? on_btn_caption : off_btn_caption , 20 , 110, 160, 80);
            btn.setAttribute('oncaption',typepopup==0 ? off_btn_caption : on_btn_caption);
            btn.setAttribute('type','tumbler');
            btn.setAttribute('color1',typepopup==0 ? on_btn_color1 : off_btn_color1);
            btn.setAttribute('color2',typepopup==0 ? on_btn_color2 : off_btn_color2);
            btn.setAttribute('oncolor1',typepopup==0 ? off_btn_color1 : on_btn_color1);
            btn.setAttribute('oncolor2',typepopup==0 ? off_btn_color2 : on_btn_color2);
            btn.setAttribute('state', typepopup==0 ? rron : rroff);
            btn.setAttribute('param',typepopup==0 ? rron : rroff);
            btn.setAttribute('r',10);
        }
        default:{
                
        }    
    }
    
}



mainlib.armatura_popup_header =  function(el, header){
    mainlibutil.svg.create_header(el,
        10,10,80,180, 5, 5,
        'fill: #333; stroke: white; stroke-with: 1; cursor: default;',
        header,
        'background: transparent; color: white; '+
        'text-align: center; vertical-align: middle;' +
        'font-family: sans-serif; font-size: 14px;');
}


mainlib.armatura_popup = function(el, header, type, on, off, ron , roff, rauto){
    
    try{
        
        var popup_id = el.getAttribute('id') + '__popupmotor';
    
        var body = mainlib.armatura_popupbody(el);
     
        var litedoc = mainlibutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = mainlibutil.svg.create_svg(litedocElement, 0 , 0,  200, 200);
        root.setAttribute('id', popup_id);

        mainlib.armatura_popup_content(popup_id, root , header, type, on, off, ron, roff, rauto);
 
        var generated = mainlibutil.xslttransform.tranform_and_getById(litedoc,popup_id);
          
        mainlib.armatura_popup_header(body,header);
    
        body.appendChild(generated.cloneNode(true));
    
    
 
    }
    catch(error){
        throw error;
    }  

}

mainlib.armatura_auto_popup = function(el, header, type, on, off, auto, ron , roff, rauto){
    
    try{
        
        var popup_id = el.getAttribute('id') + '__popupmotor';
    
        var body = mainlib.armatura_popupbody(el);
     
        var litedoc = mainlibutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = mainlibutil.svg.create_svg(litedocElement, 0 , 0,  200, 200);
        root.setAttribute('id', popup_id);
    
    
        mainlib.armatura_popup_content(popup_id, root , header, type, on, off, ron, roff, auto, rauto);
 
        var generated = mainlibutil.xslttransform.tranform_and_getById(litedoc,popup_id);
        
        mainlib.armatura_popup_header(body,header);
    
        body.appendChild(generated.cloneNode(true));
    
 
    }
    catch(error){
        throw error;
    }  

}

function main_motor_click(el, header, ron){
    //var target=ts;
    //if (!target) return;
    var target=el;
    if (el.getAttribute('state')=='disable') return;
    
    if (!el.getAttribute('id')) return;
    
    /*alert(el.getAttribute('id') + ' x:' + parseFloat(el.getAttribute('x'))
                                + ' y:' + parseFloat(el.getAttribute('y'))
                                + ' width:' + parseFloat(el.getAttribute('width'))
                                + ' height:' + parseFloat(el.getAttribute('height')));
                            
                            return;*/
    
    if (el.popup) {
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
        return;
    }
    
    //if (el.getAttribute('cursor')!='pointer') return;
    
    
    
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

function main_motor_click(el, header, ron){
    
}
    
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
    
    
    
    


