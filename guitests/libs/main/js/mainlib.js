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

mainlib.element.create_rect = function (parent, id, x , y, width, height){
    if (!parent) return;
    var newel = mainlib.element.create('rect', parent);
    if (!newel) return;
    if (id) newel.setAttribute('id', id);
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

    el.popup = libutil.popup.createsvgs(el,width,height,0, null, 'fill: white; opacity: 0.4;');

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        };
    }
    
    el.popup.onmouseout = function(ev){
         
        if (!libutil.dom.check_is_parent (el.popup,ev.toElement,true)){
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
    libutil.svg.create_header(el,
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
     
        var litedoc = libutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = libutil.svg.create_svg(litedocElement, 0 , 0,  200, 200);
        root.setAttribute('id', popup_id);

        mainlib.armatura_popup_content(popup_id, root ,  type,  ron, roff);
 
        var generated = libutil.xslttransform.tranform_and_getById(litedoc,popup_id);
          
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
     
        var litedoc = libutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = libutil.svg.create_svg(litedocElement, 0 , 0,  250, 200);
        root.setAttribute('id', popup_id);
    
    
        mainlib.armatura_popup_content(popup_id, root ,  type,  ron, roff, auto, rauto);
        mainlib.armatura_popup_autocontent(popup_id, root , rauto);
 
        var generated = libutil.xslttransform.tranform_and_getById(litedoc,popup_id);
        
        mainlib.armatura_popup_header(body,header);
    
        body.appendChild(generated);
    
 
    }
    catch(error){
        throw error;
    }  

}


mainlib.value_popupbody  = function(el, width, height){
    
    if (el.popup){
        el.popup.parentNode.removeChild(el.popup);
        el.popup=undefined;
        return;
    }

    el.popup = libutil.popup.createsvgs(el,width,height,4, null, 'fill: white; opacity: 0.9;');

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        };
    }
    
    el.popup.onmouseout = function(ev){
         
        if (!libutil.dom.check_is_parent (el.popup,ev.toElement,true)){
            el.popup.parentNode.removeChild(el.popup);
            el.popup=undefined;
        }
    };  
      
return el.popup.popupbody;  
}

mainlib.valueset_click =  function (el, nm, width){
    try{
        if (width<80) width=80;
        var popup_id = el.getAttribute('id') + '__popupvalueset';
        
        if (!parseFloat(width)) width=130;
        var b_sz = width * 35 /117 ;
        var margin_width = width * 3 /117;
        
        var margin_x1 = margin_width;
        var margin_x2 = margin_width * 2 + b_sz;
        var margin_x3 = margin_width * 3 + 2 * b_sz;
        
        var margin_top = width * 40 /130;
        
        var margin_top_y = width * 40 /130 / 20;
        var margin_top_height= width * 40 /130 * 0.9;
        var margin_top_x = width * 0.05;
        var margin_top_width = width * 0.9;
        
        var margin_text_centre = width * 40 /130 * 0.5;
        var margin_text_right = width * 0.85;
        
        var textsize = parseInt(margin_top_height * 0.50);
        
        var btntextsize = parseInt(margin_top_height * 0.6);
        
        //alert(textsize);
        
        var off_btn_color1='#800';
        var off_btn_color2='#B00';
        var on_btn_color1='#080';
        var on_btn_color2='#0B0';
        
        var stylecalc = "textsize: " + textsize+ 'px ; fill: white;text-anchor: end;  dominant-baseline: central; -webkit-user-select: none;';
        var stylebtn = "textsize: " + btntextsize+ 'px ; fill: white;';
        
        
        
        var margin_y1 = margin_top;
        var margin_y2 = margin_top + margin_width * 1 + b_sz;
        var margin_y3 = margin_top + margin_width * 2 + 2 * b_sz;
        var margin_y4 = margin_top + margin_width * 3 + 3 * b_sz;
        
        var margin_y5 = margin_top + margin_width * 4 + 4 * b_sz;
        
        var popheight = margin_top + margin_width * 5 + 5 * b_sz
        
        
        var body = mainlib.value_popupbody(el,width,popheight);
        
        var litedoc = libutil.xslttransform.literootDocument();
    
        var litedocElement = litedoc.documentElement;
    
        var root = libutil.svg.create_svg(litedocElement, 0 , 0, popheight,  width);
        root.setAttribute('id', popup_id);
        
        //var txt = libutil.svg.create_text(root, 20,20, null,null,'?' );
        //txt.setAttribute('id', popup_id+'text');
        
   
        var fnc_num = function(num) {return "var txtel= document.getElementById('"+popup_id+"_text'); if (txtel) txtel.textContent=txtel.textContent+'" + num.toString() +"';"}
        var fnc_clear = "var txtel= document.getElementById('"+popup_id+"_text'); if (txtel && txtel.textContent.length>0) txtel.textContent=txtel.textContent.substring(0, txtel.textContent.length-1);";
        var fnc_clearpopup = "var popuptmp= document.getElementById('"+popup_id+"');  if (popuptmp && popuptmp.clearpopup) popuptmp.clearpopup();";
        var fnc_cmd = "var txtel= document.getElementById('"+popup_id+"_text'); if (txtel && txtel.textContent.length>0) { $$(('" + nm +  
                           "@=' + " +"txtel.textContent" +"));} var popuptmp= document.getElementById('"+popup_id+"');  if (popuptmp && popuptmp.clearpopup) popuptmp.clearpopup();";


        //alert(fnc_cmd);
        
        
        var btn1 = mainlib.element.create_button(root, popup_id + '_buttoncalc1', '1' , margin_x1 , margin_y1 , b_sz , b_sz);
        btn1.setAttribute("onclick", fnc_num(1));
        btn1.setAttribute("fontstyle", stylebtn);
        
        var btn2 = mainlib.element.create_button(root, popup_id + '_buttoncalc2', '2' , margin_x2 , margin_y1 , b_sz,  b_sz);
        btn2.setAttribute("onclick", fnc_num(2));
        btn2.setAttribute("fontstyle", stylebtn);
        
        var btn3 = mainlib.element.create_button(root, popup_id + '_buttoncalc3', '3' , margin_x3 , margin_y1 , b_sz,  b_sz);
        btn3.setAttribute("onclick", fnc_num(3));
        btn3.setAttribute("fontstyle", stylebtn);
        
        var btn4 = mainlib.element.create_button(root, popup_id + '_buttoncalc4', '4' , margin_x1 , margin_y2 , b_sz , b_sz);
        btn4.setAttribute("onclick", fnc_num(4));
        btn4.setAttribute("fontstyle", stylebtn);
        
        var btn5 = mainlib.element.create_button(root, popup_id + '_buttoncalc5', '5' , margin_x2 , margin_y2 , b_sz,  b_sz);
        btn5.setAttribute("onclick", fnc_num(5));
        btn5.setAttribute("fontstyle", stylebtn);
        
        var btn6 = mainlib.element.create_button(root, popup_id + '_buttoncalc6', '6' , margin_x3 , margin_y2 , b_sz,  b_sz); 
        btn6.setAttribute("onclick", fnc_num(6));
        btn6.setAttribute("fontstyle", stylebtn);
        
        var btn7 = mainlib.element.create_button(root, popup_id + '_buttoncalc7', '7' , margin_x1 , margin_y3 , b_sz , b_sz);
        btn7.setAttribute("onclick", fnc_num(7));
        btn7.setAttribute("fontstyle", stylebtn);
        
        var btn8 = mainlib.element.create_button(root, popup_id + '_buttoncalc8', '8' , margin_x2 , margin_y3 , b_sz,  b_sz);
        btn8.setAttribute("onclick", fnc_num(8));
        btn8.setAttribute("fontstyle", stylebtn);
        
        var btn9 = mainlib.element.create_button(root, popup_id + '_buttoncalc9', '9' , margin_x3 , margin_y3 , b_sz,  b_sz);
        btn9.setAttribute("onclick", fnc_num(9));
        btn9.setAttribute("fontstyle", stylebtn);
        
        var btnp = mainlib.element.create_button(root, popup_id + '_buttoncalcp', '.' , margin_x1 , margin_y4 , b_sz , b_sz);
        btnp.setAttribute("onclick", fnc_num('.'));
        btnp.setAttribute("fontstyle", stylebtn);
        
        var btn0 = mainlib.element.create_button(root, popup_id + '_buttoncalc0', '0' , margin_x2 , margin_y4 , b_sz,  b_sz);
        btn0.setAttribute("onclick", fnc_num(0));
        btn0.setAttribute("fontstyle", stylebtn);
         
        var btnc = mainlib.element.create_button(root, popup_id + '_buttoncalcc', 'C' , margin_x3 , margin_y4 , b_sz,  b_sz);
        btnc.setAttribute("onclick", fnc_clear);
        btnc.setAttribute("fontstyle", stylebtn);
        
        var btnm = mainlib.element.create_button(root, popup_id + '_buttoncalcm', '-' , margin_x1 , margin_y5 , b_sz,  b_sz);
        btnm.setAttribute("onclick", fnc_num('-'));
        btnm.setAttribute("fontstyle", stylebtn);
        
        var btncancel = mainlib.element.create_button(root, popup_id + '_buttoncalcancel', 'x' , margin_x2 , margin_y5 , b_sz,  b_sz);
        btncancel.setAttribute("onclick", fnc_clearpopup);
        btncancel.setAttribute('color1',off_btn_color1);
        btncancel.setAttribute('color2',off_btn_color2); 
        btncancel.setAttribute("fontstyle", stylebtn);
        
        var btnok = mainlib.element.create_button(root, popup_id + '_buttonok', 'ok' , margin_x3 , margin_y5 , b_sz,  b_sz);
        btnok.setAttribute("onclick", fnc_cmd);
        btnok.setAttribute('color1',on_btn_color1);
        btnok.setAttribute('color2',on_btn_color2);
        btnok.setAttribute("fontstyle", stylebtn);
        
        var generated = libutil.xslttransform.tranform_and_getById(litedoc,popup_id);
        
         
        body.appendChild(generated);
        
        libutil.svg.create_rect(body,  margin_top_x , margin_top_y , margin_top_height , margin_top_width , 3, 3 );
        
        var trpopup =document.getElementById(popup_id);
        if (trpopup){
            trpopup.clearpopup = function(){
                el.popup.parentNode.removeChild(el.popup);
                el.popup=undefined;
            }
        }   
        
        var txt = libutil.svg.create_text(body , margin_text_right  ,  margin_text_centre  , stylecalc , null, '' );
        txt.setAttribute('id', popup_id+'_text');

        
        
    }
    catch(error){
        throw error;
    }  
}

    
//gw.appendChild(btnonrect);
    
mainlib.graph_click =  function (nm){
    var tgnm=nm;
    var idtgnm=nm + '_divelem';
    var newwin = open('', event.target , "toolbar=0,location=0,left=400,top=200, width=650,height=250");
    newwin.document.open();    
    newwin.document.write('<?xml version="1.0" encoding="UTF-8"?>');
    newwin.document.write('   <html>');
    newwin.document.write('      <head>');
    newwin.document.write('<script type="text/javascript" src="../util/js_ext/hightchart/jquery.min.js"></script>');
    newwin.document.write('<script type="text/javascript" src="../util/js_ext/hightchart/highcharts.js"></script>');
    newwin.document.write('<script type="text/javascript" src="../util/js_ext/hightchart/exporting.js"></script>');
    newwin.document.write('<script type="text/javascript" src="../libs/main/js/hightrend.js"></script>');
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
    
    
    
    


