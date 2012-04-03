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




mainlib.armatura_popupbody  = function(el, width, height){
    if (el.popup){
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
        return;
    }

    el.popup = mainlibutil.popup.createsvgs(el,width,height,0, null, 'fill: white; opacity: 0.4;');

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        };
    }
    
    el.popup.onmouseout = function(ev){
         
        if (!mainlibutil.dom.check_is_parent (el.popup,ev.toElement,true)){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        }
    };  
      
return el.popup.popupbody;  
}





mainlib.armatura_popup_content =  function(id, el,  type,  rron, rroff, auto, rauto){
    
    var on_btn_caption = (type=='motor' ? 'Пуск' : 'Открыть');
    var off_btn_caption = (type=='motor' ? 'Стоп' : 'Закрыть');
    var stop_btn_caption = (type=='motor' ? 'Сброс' : 'Стоп');   
    var off_btn_color1='#800';
    var off_btn_color2='#B00';
    var on_btn_color1='#080';
    var on_btn_color2='#0B0';
    var stop_btn_color1='#880';
    var stop_btn_color2='#BB0';
    
    var littlstyle ='font-size: 11; fill: white;';
    
    var isauto = (auto && rauto && (auto!='') && (rauto!=''));
    
    var valid = '';
    if (rron && (rron!=''))
        valid = valid=='' ? (valid + rron) : (valid + ' || ' +rron);
    if (rroff && (rroff!=''))
        valid = valid=='' ? (valid + rroff) : (valid + ' || ' +rroff);
    if (auto && (auto!=''))
        valid = valid=='' ? (valid + auto) : (valid + ' || ' +auto);
    
    valid = (valid!='') ? '(!('+valid+').valid)' : undefined;
    
    if (isauto)
        valid = (valid) ? auto + ' || ' + valid : auto;
    
    
    var typepopup = ((rron!='') && (rroff!='')) ? 2 : ((rron!='') ? 0 : 1);
    
    switch(typepopup){
        case 0:
        case 1:{
            var btn = mainlib.element.create_button(el, id + '_onoffbutton', typepopup==0 ? on_btn_caption : off_btn_caption , 20 , 95, 160, 100);
            btn.setAttribute('oncaption',typepopup==0 ? off_btn_caption : on_btn_caption);
            btn.setAttribute('dsblcaption','  ');
            btn.setAttribute('type','tumbler');
            btn.setAttribute('color1',typepopup==0 ? on_btn_color1 : off_btn_color1);
            btn.setAttribute('color2',typepopup==0 ? on_btn_color2 : off_btn_color2);
            btn.setAttribute('oncolor1',typepopup==0 ? off_btn_color1 : on_btn_color1);
            btn.setAttribute('oncolor2',typepopup==0 ? off_btn_color2 : on_btn_color2);
            btn.setAttribute('state', typepopup==0 ? rron : rroff);
            btn.setAttribute('param',typepopup==0 ? rron : rroff);
            //alert(valid);
            if (valid)
                btn.setAttribute('disable',valid);
            btn.setAttribute('r',10);
            break;
        }
        default:{
               
            var btnon = mainlib.element.create_button(el, id + '_onbutton', on_btn_caption , 20 , 95 , 160, 33);      
            btnon.setAttribute('color1',on_btn_color1);
            btnon.setAttribute('color2',on_btn_color2);
            btnon.setAttribute('param',rron + ' @ 1');
            btnon.setAttribute('fontstyle',littlstyle);
            if (valid)
                btnon.setAttribute('disable',valid);
            btnon.setAttribute('r',5);
            
            var btnstop = mainlib.element.create_button(el, id + '_stopbutton', stop_btn_caption , 20 , 130, 160, 33);          
            btnstop.setAttribute('color1',stop_btn_color1);
            btnstop.setAttribute('color2',stop_btn_color2);
            btnstop.setAttribute('disable','!('+rron+' || '+rroff+')' + (isauto ? (' || ' + auto ) : ''));
            btnstop.setAttribute('param','(('+rron+' @ 0) || ('+rroff+' @ 0))');
            btnstop.setAttribute('fontstyle',littlstyle);
            btnstop.setAttribute('r',5);
            
            var btnoff = mainlib.element.create_button(el, id + '_offbutton', off_btn_caption , 20 , 165 , 160, 33);           
            btnoff.setAttribute('color1',off_btn_color1);
            btnoff.setAttribute('color2',off_btn_color2);
            btnoff.setAttribute('param',rroff + ' @ 1');
            btnoff.setAttribute('fontstyle',littlstyle);
            if (valid)
                btnoff.setAttribute('disable',valid);            
            btnoff.setAttribute('r',5);
            
            break;
        }    
    }
    
}




mainlib.armatura_popup_autocontent =  function(id, el, rauto){
    var littlstyle ='font-size: 11; fill: white;';
    var btn = mainlib.element.create_button(el, id + '_autobutton', 'В автомат.' , 20 , 210 , 160, 30);
    btn.setAttribute('oncaption','В дист.');
    btn.setAttribute('type','tumbler');
    btn.setAttribute('state', rauto);
    btn.setAttribute('param',rauto);
    btn.setAttribute('fontstyle',littlstyle);

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





mainlib.armatura_popup = function(el, header, type, ron , roff){
    
    try{
        
        var popup_id = el.getAttribute('id') + '__popupmotor';
    
        var body = mainlib.armatura_popupbody(el,200,200);
     
        var litedoc = mainlibutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = mainlibutil.svg.create_svg(litedocElement, 0 , 0,  200, 200);
        root.setAttribute('id', popup_id);

        mainlib.armatura_popup_content(popup_id, root , type,  ron, roff);
 
        var generated = mainlibutil.xslttransform.tranform_and_getById(litedoc,popup_id);
          
        mainlib.armatura_popup_header(body,header);
    
        body.appendChild(generated);
    
    
    
 
    }
    catch(error){
        throw error;
    }  

}

mainlib.armatura_auto_popup = function(el, header, type, auto, ron , roff, rauto){
    
    try{
        
        var popup_id = el.getAttribute('id') + '__popupmotor';
    
        var body = mainlib.armatura_popupbody(el,200,250);
     
        var litedoc = mainlibutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = mainlibutil.svg.create_svg(litedocElement, 0 , 0,  250, 200);
        root.setAttribute('id', popup_id);
    
    
        mainlib.armatura_popup_content(popup_id, root ,  type,  ron, roff, auto, rauto);
        mainlib.armatura_popup_autocontent(popup_id, root , rauto);
 
        var generated = mainlibutil.xslttransform.tranform_and_getById(litedoc,popup_id);
        
        mainlib.armatura_popup_header(body,header);
    
        body.appendChild(generated);
    
 
    }
    catch(error){
        throw error;
    }  

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
    newwin.document.close();
}
    
//documentElement.appendChild(svg);
    
    
    
    


