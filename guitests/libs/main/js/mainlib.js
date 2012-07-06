var mainlib = {    
    
};

mainlib.NAMESPACE_URL = 'http://dvnci/mlib';

mainlib.CHART_WIDTH = 350;

mainlib.CHART_HEIGHT = 180;

mainlib.CHART_PADDING = 5;

mainlib.REGULATOR_WIDTH = 250;

mainlib.REGULATOR_S_HEIGHT = 320;

mainlib.REGULATOR_F_HEIGHT = 494;

mainlib.POPUP_R = 10;

mainlib.POPUP_BODY_STYLE = 'fill: #333; opacity: 0.1; ';

mainlib.POPUP_STATIC_STYLE = 'fill: #333; fill-opacity: 0.4; stroke: yellow; stroke-width: 1; stroke-opacity: 1.0 ';

mainlib.POPUP_MOVE_STYLE = 'fill: yellow; fill-opacity: 0.3; stroke: green; stroke-width: 1; stroke-opacity: 1.0'

mainlib.element = {};


mainlib.check_click = function(el , ev){
    if (el && el.correspondingUseElement && el.correspondingUseElement.parentNode){
        var needofsetrect = el.correspondingUseElement.parentNode.getBoundingClientRect();
        //console.log('bbox',needofsetrect);
    }
    var target =el.correspondingElement ? el.correspondingElement : el;
    if (target && target.getAttribute && target.getAttribute('cursor')=='pointer'){
        target.needofsetrect = needofsetrect;
        return target;}
    return null;
}

mainlib.create_shadow_slider =  function (el, x1, y1 , x2, y2 , direction , tag, live, wait){
    
    var parent=el.parentNode;
    
    if (el.movelement){
        parent.onmousemove=undefined;
        parent.onmouseout=undefined;
        parent.onmouseup=undefined;
        parent.removeChild(el.movelement);
    }
    
    var dupl = libutil.dom.duplicateElement(el, false, ['id','captured','onmousedown', 'onmouseup']);

    el.movelement = dupl;
    
    dupl.minx =x1;
    dupl.maxx =x2;
    dupl.miny =y1;
    dupl.maxy =x1;
    
    dupl.startx =event.x ;
    dupl.starty =event.y;
    
    dupl.startcx =parseInt(dupl.getAttribute('x'));
    dupl.startcy =parseInt(dupl.getAttribute('y'));
    
    dupl.reverse =(direction=='rl') || (direction=='bt');
    dupl.vertical =(direction=='tb') || (direction=='bt');
    
    dupl.lengthline = dupl.vertical ? (dupl.maxy - dupl.miny) : (dupl.maxx - dupl.minx);
    
    parent.appendChild(dupl);
    
    var selfremove = function(){
        parent.onmousemove=undefined;
        parent.onmouseout=undefined;
        parent.onmouseup=undefined;
        if (el.movelement){
            el.movelement.onmouseout=undefined;
            el.movelement.onmousemove=undefined;
            el.movelement.onmouseup=undefined;      
            parent.removeChild(el.movelement);
            el.movelement=undefined;
        }
    }
    
    dupl.onselectstart = function(ev){
           ev.stopPropagation();
           ev.preventDefault();
           return false;}
    
    dupl.onmousemove = function(ev){
        var newv = dupl.vertical ? ev.y - dupl.starty : ev.x - dupl.startx;
        if (newv){
            var newval = (dupl.vertical ? dupl.startcy  : dupl.startcx) + newv;
            dupl.setAttribute(dupl.vertical ? 'y' : 'x' ,newval);
            if (live){
                var cmdlength = dupl.vertical ? (dupl.reverse ? dupl.maxy - newval:  newval - dupl.miny) 
                : (dupl.reverse ? dupl.maxx - newval: newval - dupl.minx);
                command(cmdlength/dupl.lengthline);
            }
        }  
    }
    
    
    dupl.onmouseup=function(ev){
        var newv = dupl.vertical ? ev.y - dupl.starty : ev.x - dupl.startx;
        if (newv){            
            var newval = (dupl.vertical ? dupl.startcy  : dupl.startcx) + newv;
            var cmdlength = dupl.vertical ? (dupl.reverse ? dupl.maxy - newval:  newval - dupl.miny) 
            : (dupl.reverse ? dupl.maxx - newval: newval - dupl.minx);
            command(cmdlength/dupl.lengthline);
            setTimeout(function() {
                selfremove();
                el.onmouseup();
            }, (wait && parseInt(wait)) ? wait : 3000  );
        }
        else{
            selfremove();
            el.onmouseup();
        }
    }    
  
    
    
    var command = function(val){
        try{
            var cmd = tag + ' @@= ('+ tag +'.mineu + ((' + tag + '.maxeu - ' + tag + '.mineu) * ' + val.toString()+ '))';
            console.log('val:' + val +' min:' + $$(tag +'.mineu') +' max:' + $$(tag +'.maxeu'))
            $$(cmd);
        }
        catch(error){
            console.log('Command slider no set:' + error)
        }
    }
    
    parent.onselectstart = function(ev){
           ev.stopPropagation();
           ev.preventDefault();
           return false;}
    
    parent.onmousemove = function(ev){
        if (el.movelement) {
            el.movelement.onmousemove(ev);
            ev.stopPropagation();
        }
    }    

    
    parent.onmouseout = function(ev){

        if (!libutil.dom.checkIsParent (parent,ev.toElement,true)){
            selfremove();
            el.onmouseup(ev);
        }
    }
    
    parent.onmouseup = function(ev){
        if (el.movelement){
            el.movelement.onmouseup(ev);
        }
        else{
            el.onmouseup(ev);
        }
        

    }
       
}




mainlib.get_popupbody  = function(el, width, height, remfunc , shift, namepopup){
    
    if (!namepopup) namepopup='popup';
    var namepopupold='old'+namepopup;
    
    if (el[namepopup]){
        return;
    }

    el[namepopup] = libutil.popup.createsvgs(el,width,height,0, null, mainlib.POPUP_BODY_STYLE , null, mainlib.POPUP_R, shift);
    
    if (el[namepopupold]){
        var x=parseInt(el[namepopup].getAttribute('x'));
        var y=parseInt(el[namepopup].getAttribute('y'));
        el[namepopup].parentNode.removeChild(el[namepopup]);
        el[namepopup]=el[namepopupold];
        el[namepopup].setAttribute('x', x);
        el[namepopup].setAttribute('y', y);
        el[namepopup].setAttribute('style', '');
        return undefined;
    }
    
    el[namepopup].setAttribute('cursor', 'pointer');
    

    
    if (el[namepopup].firstChild) {
        el[namepopup].firstChild.onclick= function(){
            el[namepopup].setAttribute('style', 'display: none;');
        };
    }
    
    el[namepopup].onmouseout = function(ev){
        
        if (!libutil.dom.checkIsParent (el[namepopup],ev.toElement,true)){
            if (remfunc)
                    remfunc();
            else
               el[namepopup].setAttribute('style', 'display: none;'); 
        }
        
       
    };  

    el[namepopup].onmousedown= function(){
        
        if (event.target==el[namepopup]){

         
            if (el[namepopup]){
                
                if (remfunc)
                    remfunc();
                else
                    el[namepopup].setAttribute('style', 'display: none;');               
            }
           
        }
    }; 
      
    return el[namepopup].popupbody;  
}



mainlib.get_staticpopupbody  = function(el, width, height, remfunc, shift, namepopup){
    
    if (!namepopup) namepopup='popup';
    
    if (!el[namepopup]){
    el[namepopup] = libutil.popup.createsvgs(el,width,height,4, null , mainlib.POPUP_BODY_STYLE , 
                                        mainlib.POPUP_STATIC_STYLE , mainlib.POPUP_R);

    var mainpopup = el[namepopup]; 
    var hoverrect = mainpopup.hoverrect;
    var btnparent = el[namepopup];
    var btnpos = el[namepopup].buttonposition;
    
    var size = btnpos.width < btnpos.height ? 
        btnpos.width : btnpos.height;
    var cx = btnpos.x + btnpos.width / 2;
    var cy = btnpos.y + btnpos.height / 2;
    var sizeR = size / 2;
    if (sizeR>16) sizeR= 16; 
    var x = cx - sizeR / 2;
    var y = cy - sizeR / 2;
    if (btnpos.dir===0 || btnpos.dir==2)
        x = btnpos.width - 2 * sizeR; 
    if (btnpos.dir==1 || btnpos.dir==3)
        y = btnpos.height - 2 * sizeR;   
    
    this.closebutton = libutil.svg.create_element( 'image', btnparent,   [{
        name : 'x' , 
        value: x
    },

    {
        name : 'y' , 
        value: y
    },      

    {
        name : 'height' , 
        value: sizeR
    },

    {
        name : 'width' , 
        value: sizeR
    }]);


    var rootbody = el[namepopup];
    
    var rootbodyreplace = function(x,y ,func){
        rootbody.style.display='none';
        setTimeout( function(){
            rootbody.setAttribute('x', x);
            rootbody.setAttribute('y', y);
            if (func ) func();
            rootbody.style.display='block';
            rootbody.needofsetrect = rootbody.getBoundingClientRect();
        },10);
    }
    
    
    el[namepopup].rootbodyreplace=rootbodyreplace;
    
    

        
    var cteateshadowboby = function(){
        
        el.hoverrectrootel = libutil.svg.create_element('svg', rootbody.parentNode  , [
            {name : 'x', 
                value:  rootbody.x.baseVal.value-400
            },

            {
                name : 'y', 
                value:  rootbody.y.baseVal.value-400
            },

            {
                name : 'width', 
                value: rootbody.width.baseVal.value+800
            },

            {
                name : 'height', 
                value: rootbody.height.baseVal.value+800
            }]);
        
    

        el.hoverrectshadow = libutil.svg.create_element('rect', el.hoverrectrootel  , [{
            name : 'x', 
            value:  400
        },

        {
            name : 'y', 
            value:  400
        },

        {
            name : 'width', 
            value: rootbody.width.baseVal.value
            },

            {
            name : 'height', 
            value: rootbody.height.baseVal.value
            },

            {
            name : 'rx', 
            value: mainlib.POPUP_R
            },

            {
            name : 'ry', 
            value: mainlib.POPUP_R
            }, 
            {
            name : 'cursor', 
            value: 'pointer'
            },             


            {
            name : 'style', 
            value : mainlib.POPUP_MOVE_STYLE
        }]);
    
           el.hoverrect = libutil.svg.create_element('rect', el.hoverrectrootel  , [{
                name : 'x', 
                value:  0
            },

            {
                name : 'y', 
                value:  0
            },

            {
                name : 'width', 
                value: rootbody.width.baseVal.value+800
            },

            {
                name : 'height', 
                value: rootbody.height.baseVal.value+800
            },
 
            {
                name : 'cursor', 
                value: 'pointer'
            },             


            {
                name : 'style', 
                value : 'opacity: 0; fill: white;'
            }]);
    
    
    
        el.hoverrect.onselectstart = function(ev){
           ev.stopPropagation();
           ev.preventDefault();
           return false;}
       
          
    
        el.hoverrect.onmousemove = function(ev){
            if (ev.target==el.hoverrect && el.hoverrect.captured){
                if ((el.hoverrect.captured.x!=ev.x) || (el.hoverrect.captured.y!=ev.y)) {
                    var shiftX = el.hoverrect.captured.x - ev.x;
                    var shiftY = el.hoverrect.captured.y - ev.y;
                    
                    el.hoverrectrootel.setAttribute('x', parseInt(el.hoverrectrootel.getAttribute('x'))-shiftX );
                    el.hoverrectrootel.setAttribute('y', parseInt(el.hoverrectrootel.getAttribute('y'))-shiftY );
                    el.hoverrect.changerect =true;
                    el.hoverrect.captured=ev;
                }
            }
        }
    
        el.hoverrect.onmouseup = function(ev){
            if (ev.target==el.hoverrect){
                el.hoverrect.captured = undefined;                
                if (!el.hoverrect.changerect){
                    el.hoverrectrootel.parentNode.removeChild(el.hoverrectrootel);
                    return;
                }     
                rootbodyreplace(parseInt(ev.x - el.hoverrect.capturedstart.x) +  parseInt(rootbody.getAttribute('x')),
                                parseInt(ev.y - el.hoverrect.capturedstart.y) +  parseInt(rootbody.getAttribute('y')),
                                         function(){el.hoverrectrootel.parentNode.removeChild(el.hoverrectrootel);} );
            }        
        }
    
        el.hoverrect.onmousedown = function(ev){
            el.hoverrect.captured = ev;
            el.hoverrect.capturedstart = ev;
            //console.log('shadow mousedown');
            ev.stopPropagation();            
        }
        
        el.hoverrect.onmouseout = function(ev){
            if (ev.target==el.hoverrect && el.hoverrect.captured){
                el.hoverrect.onmouseup(ev);
                ev.stopPropagation();
            }          
        }        
    
    }   

    this.closebutton.setAttributeNS(libutil.XLINK_NAMESPACE_URL, 'xlink:href', '../util/css/res/close.svg' );

    this.closebutton.onclick = function(ev){       
            if (remfunc)
                remfunc();
            else
                el[namepopup].parentNode.removeChild(el[namepopup]);      
    
    }
    

    hoverrect.onselectstart = function(ev){
           ev.stopPropagation();
           ev.preventDefault();
           return false;}    

    
    hoverrect.onmousedown = function(ev){
        if (ev.target==hoverrect){ 
          cteateshadowboby();  
          el.hoverrect.onmousedown(ev);
        }            
    }
              
    el[namepopup].setAttribute('cursor', 'pointer');
    }
    else
    {
       el[namepopup].rootbodyreplace(el[namepopup].boundspopup.x , el[namepopup].boundspopup.y);
       return null;
    }    
   
    return el[namepopup].popupbody;  
}





mainlib.armatura_popup = function(el, rauto){
    if (el.popup){
        el.popup.setAttribute('style', '');
        return;
    }
    try{
        
        var body = mainlib.get_popupbody(el,150, (libutil.util.trim(rauto)=='') ? 150 : 188);
        
        document.getElementById(el.getAttribute('id') + '_popup');
           
           
        var use = libutil.svg.create_element('use', body);
        body.useelement=use;
        use.setAttributeNS(libutil.XLINK_NAMESPACE_URL,'href','#'+el.getAttribute('id') + '_popup');

    }
    catch(error){
        throw console.error('mainlib.armatura_popup error: ' + error);
    }  


}


mainlib.valueset_click =  function (el, nm, width){
    
    var popupid = 'calcpopup__';
    var okbutton = document.getElementById(popupid  + '_popup_buttonok');
    var text = document.getElementById(popupid  + '_popup_sensorcalc_sensor_text'); 
    var tag = nm;
    
    if (el.popup){       
        if (text)
            text.textContent='';
        el.popup.setAttribute('style', '');
        okbutton.onclick = function(){
            $$(tag + ' @ ' + text.textContent);
            if (el.popup.trpopup && el.popup.trpopup.clearpopup) el.popup.trpopup.clearpopup(); };
        return;
    }
    
    try{
        if (width<100) width=100;
       
   
        var body = mainlib.get_popupbody(el,width,parseFloat(width)* 2.05, 
                                         el.needofsetrect ? function() {
                                             if (el.popup) {el.popup.setAttribute('style', 'display: none;');okbutton.onclick = undefined; el.oldpopup= el.popup;el.popup=undefined;}} : null, 
                                         el.needofsetrect);
       
        
        if (text)
            text.textContent='';   
        
        if (!body){
            okbutton.onclick = function(){
            $$(tag + ' @ ' + text.textContent);
            if (el.popup.trpopup.clearpopup && el.popup.trpopup.clearpopup) el.popup.trpopup.clearpopup(); };
        return;
        } 
            
                                         
        body.setAttribute('id',el.getAttribute('id') + '_popup_body');
        

        
        el.popup.trpopup =document.getElementById(el.getAttribute('id') + '_popup_body');
        if (el.popup.trpopup){
            el.popup.trpopup.clearpopup = function(){
                if (el.needofsetrect){
                   if (el.popup) {el.popup.setAttribute('style', 'display: none;'); el.oldpopup= el.popup;el.popup=undefined;okbutton.onclick = undefined;}}
                else {
                    el.popup.setAttribute('style', 'display: none;');okbutton.onclick = undefined;}
                }
                

        }   
            
            
        
        var defs = document.getElementById(popupid  + '_popup');
        
        var use = libutil.svg.create_element('use', body);
        body.useelement=use;
        use.setAttributeNS("http://www.w3.org/1999/xlink",'href','#'+popupid  + '_popup');
        okbutton.onclick = function(){
            $$(tag + ' @ ' + text.textContent);
            if (el.popup.trpopup.clearpopup && el.popup.trpopup.clearpopup) el.popup.trpopup.clearpopup(); };
        
        
        
    }
    catch(error){
        throw error;
    }  
}



mainlib.valueedit_click =  function (el, nm, alighn, r, stroke, strokewidth, color1, color2, format, fontcolor, fontstyle){
    
  var parent =  el.needofsetrect ? document.documentElement : el.parentNode;
  
  var tag = nm;
  
  var elementId =  el.getAttribute('id');
  
  var text = document.getElementById(elementId + '_sensor_text');
  
  var rect =  document.getElementById(elementId + '_sensor_rect');
  
  if (!text || !rect) return;
  
  var x = parseInt(rect.getAttribute('x'));
  var y = parseInt(rect.getAttribute('y'));
  var width = parseInt(rect.getAttribute('width'));
  var height = parseInt(rect.getAttribute('height'));
  
  if (el.needofsetrect) x=x+el.needofsetrect.left;
  if (el.needofsetrect) y=y+el.needofsetrect.top;
  
  if (!format) format = '%9.0f';
  
  var editstyle = 'margin: 0 1; padding: 0 5px ; -webkit-border-radius: ' +  ((r && parseInt(r)) ? r : '0') + 'px; ';
  editstyle = editstyle + 'border-color: transparent' +  /*(stroke ? stroke : '#0e0') +*/ '; '; 
  editstyle = editstyle + 'border-width: 0px; ';
  editstyle = editstyle + 'text-align: ' +  (alighn ? alighn : 'right') + '; ';
  editstyle = editstyle + 'background-color: ' +  (color1 ? color1 : '#111') + '; ';
  editstyle = editstyle + 'color: ' +  (fontcolor ? fontcolor : '#eee') + '; ';
  editstyle = editstyle + 'height: ' + height + 'px; ';
  editstyle = editstyle + 'width: ' + (width - 10) + 'px; ';
  editstyle = editstyle +  (text.style ? text.style.cssText : '') + '; ';
  editstyle = editstyle +  ' -webkit-user-select: text;';
  
   
  var result = libutil.svg.create_element('foreignObject', parent , [{
        name : 'x', 
        value:  x
        },
        {
        name : 'y', 
        value:  y
        },
        {
        name : 'width', 
        value: width
        },
        {
        name : 'height', 
        value : height
        }]);
    
    el.editelement =result;
    
    var html = libutil.html.create_element('html' , result);
            
    var head = libutil.html.create_element('head', html,[{
    }]);

    var htmlbody= libutil.html.create_element( 'body' ,html, [{name: 'style', value: 'margin: 0; padding: 0;'}]);
            
    var bodydiv= libutil.html.create_element('div' , htmlbody, [{name: 'style' , value: '-webkit-user-select: text;'}] );  
                                                             
    var val = $$('format('+tag+"'"+ format+ "')");                                                         
                                                             
    var edit = libutil.html.create_element('input' , bodydiv, [{name: 'value', value: val},
                                                               {name: 'type', value: 'text'},
                                                               {name: 'style', value: editstyle}]);
                                                           
                                                           
                                                           
    result.onmouseout = function(ev){
        if (parent && el.editelement){
            parent.removeChild(el.editelement);
        }       
    }  

    edit.addEventListener( 'keyup' ,function (ev) {       
            if ((ev.keyIdentifier=="Enter")){
                $$(tag+" @ "+ edit.value);
                result.onmouseout(ev);
            }});
        
    edit.focus();    
    
    //edit.textContent = "yyy";
   
  
}

   
mainlib.graph_click =  function (el, nm, color){

    var elementId =  el.getAttribute('id');
    
    if (!color) color='red';
    
    var body = mainlib.get_staticpopupbody(el,mainlib.CHART_WIDTH,mainlib.CHART_HEIGHT, 
                                           function() {if (el.popup) el.popup.parentNode.removeChild(el.popup);el.popup=undefined;}); 
    if (!body && el.popup) return;

    body.setAttribute('id',elementId + '_popup_body');
    
    var result = libutil.svg.create_element('foreignObject', body, [{
        name : 'x', 
        value:  0
        },
        {
        name : 'y', 
        value:  0
        },
        {
        name : 'width', 
        value: mainlib.CHART_WIDTH
        },
        {
        name : 'height', 
        value : mainlib.CHART_HEIGHT
        }]);   
    
    var html = libutil.html.create_element('html' , result);
            
    var head = libutil.html.create_element('head', html,[{
    }]);

    var htmlbody= libutil.html.create_element( 'body' ,html, [{name: 'style', value: 'margin: 0; padding: '+ mainlib.CHART_PADDING + 'px'}]);
            
    var bodydiv= libutil.html.create_element('div' , htmlbody, [{name : 'id' , value: elementId + '_popup_graph'},
                                                                 {name: 'style' , value: '-webkit-user-select: none'}] );    
    var script = libutil.html.create_element('script', head );
    
    var title = $$(nm+'.comment');

    script.textContent="new libutil.trendchart('"+elementId + '_popup_graph'+"','"+
                                                         elementId + '_popup_body'+
                                                         "', "+"['"+nm+"'], 600, ['"+color+"','green','blue','#880'], " + 
                                                         (mainlib.CHART_WIDTH - 2* mainlib.CHART_PADDING) + ", " +
                                                         (mainlib.CHART_HEIGHT - 2* mainlib.CHART_PADDING)+ (title ? ", 5 , { title: '"+title+"',background: [[0 , '#222'],[0.5 , '#444'],[1 , '#222']]})" : ", 5 , {background: [[0 , '#222'],[0.5 , '#444'],[1 , '#222']]})");
           
}



mainlib.regulator_click =  function (el, smp){

    var elementId =  el.getAttribute('id');
     
    var createchart = function() {
        var chartdiv = document.getElementById(elementId + '_popup_graph');
        if (chartdiv){
            var period = el.getAttribute('period').valueOf() ?    el.getAttribute('period').valueOf() : 600;
            el.popup.chart = new libutil.trendchart(elementId + '_popup_graph',
                                                    elementId + '_chart_background',eval(el.getAttribute('charts')),period, eval(el.getAttribute('colors')) ,240, 145, 5,  
                                                    {background: [[0 , '#333'],[0.5 , '#666'],[1 , '#333']]});
        }
    }
    
    var getbody = function(){
        return mainlib.get_staticpopupbody(el,mainlib.REGULATOR_WIDTH ,
            smp ? mainlib.REGULATOR_S_HEIGHT : mainlib.REGULATOR_F_HEIGHT, 
            function() {
                el.popup.setAttribute('style', 'display: none;');
                if (el.popup.chart){
                    el.popup.chart.detach();
                    el.popup.chart = undefined;
                }
            });       
    }
    
    if (el.popup){
        getbody();
        el.popup.setAttribute('style', '');
        if (!el.popup.chart){
            createchart();
        }
        return;
    }  
    try{

   
        var body = getbody();
         
        body.setAttribute('id',elementId + '_popup_body');
    
        if (!body && el.popup) return;
        
        var trpopup =document.getElementById(elementId + '_popup_body');
        if (trpopup){
            trpopup.clearpopup = function(){
                el.popup.setAttribute('style', 'display: none;');
            }
        }  
        
                
        var chartbackground = libutil.svg.create_element('svg', body, [{
            name : 'x', 
            value:  5
        },
        {
            name : 'y', 
            value:  smp ? 170 : 170 + (mainlib.REGULATOR_F_HEIGHT-mainlib.REGULATOR_S_HEIGHT)
        },
        {
            name : 'width', 
            value: 240
        },
        {
            name : 'height', 
            value : 145
        }]);
    
        chartbackground.setAttribute('id',elementId + '_chart_background');
    
    
                       
        var result = libutil.svg.create_element('foreignObject', chartbackground, [{
            name : 'x', 
            value:  0
        },
        {
            name : 'y', 
            value:  0
        },
        {
            name : 'width', 
            value: 240
        },
        {
            name : 'height', 
            value : 145
        }]);   
    
        var html = libutil.html.create_element('html' , result);
            
        var head = libutil.html.create_element('head', html,[{
            }]);


        var htmlbody= libutil.html.create_element( 'body' ,html, [{
            name: 'style', 
            value: 'margin: 0; padding: '+ 0 + 'px'
            }]);
            
        var bodydiv= libutil.html.create_element('div' , htmlbody, [{
            name : 'id' , 
            value: elementId + '_popup_graph'
            },

            {
            name: 'style' , 
            value: '-webkit-user-select: none'
        }] );
    

        
        var defs = document.getElementById(elementId + '_popup_rootbody');
        
        var use = libutil.svg.create_element('use', body);
        body.useelement=use;
        use.setAttributeNS("http://www.w3.org/1999/xlink",'href','#'+elementId + '_popup');
        
        createchart();
        
    
    }
    catch(error){
        throw error;
    }  
    
}

mainlib.config_click = function (el){
 
    if (el.configpopup){
        if (el.configpopup.getAttribute('style')!='') el.configpopup.setAttribute('style', '');
        else  el.configpopup.setAttribute('style', 'display: none;');
        return;
    }
    
    var elementId =  el.getAttribute('id');
    var defs = document.getElementById(elementId + '_popup_config');
    
    if (!defs) return;
    
    try{
        
        var width=250;
        
        var height = 30 + (defs.childNodes.length  - 1) * 12 + 4;
       
   
        var body = mainlib.get_staticpopupbody(el,width,height, 
                                         function() {if (el.configpopup) 
                                                      el.configpopup.setAttribute('style', 'display: none;');}, 
                                         el.needofsetrect, 'configpopup');
                                         
        body.setAttribute('id', elementId + '_popup_config_body');
        
                  
        
        var use = libutil.svg.create_element('use', body);
        body.useelement=use;
        use.setAttributeNS("http://www.w3.org/1999/xlink",'href','#' + elementId + '_popup_config');
        
        
        
    }
    catch(error){
        throw error;
    }  

    
}




    
    
    

