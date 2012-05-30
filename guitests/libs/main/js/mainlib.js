var mainlib = {    
    
};

mainlib.NAMESPACE_URL = 'http://dvnci/mlib';

mainlib.CHART_WIDTH = 350;

mainlib.CHART_HEIGHT = 180;

mainlib.POPUP_R = 10;

mainlib.POPUP_BODY_STYLE = 'fill: #333; opacity: 0.5; ';

mainlib.POPUP_STATIC_STYLE = 'fill: #333; fill-opacity: 0.1; stroke: #888; stroke-width: 0.5; stroke-opacity: 1.0 ';

mainlib.POPUP_MOVE_STYLE = 'fill: white; fill-opacity: 0.01; stroke: green; stroke-width: 0.5; stroke-opacity: 1.0'

mainlib.element = {};


mainlib.create_shadow_slider =  function (el, x1, y1 , x2, y2 , direction , tag, live, wait){
    
    var parent=el.parentNode;
    
    if (el.movelement){
        parent.onmousemove=undefined;
        parent.onmouseout=undefined;
        parent.onmouseup=undefined;
        //console.log('parent.onmousemove deleted INIT');
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
            //console.log('dupl.onmouseup');
            var newval = (dupl.vertical ? dupl.startcy  : dupl.startcx) + newv;
            var cmdlength = dupl.vertical ? (dupl.reverse ? dupl.maxy - newval:  newval - dupl.miny) 
            : (dupl.reverse ? dupl.maxx - newval: newval - dupl.minx);
            command(cmdlength/dupl.lengthline);
            setTimeout(function() {
                selfremove();
                el.onmouseup();
            }, (wait && parseInt(wait)) ? wait : 1000  );
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
    
    parent.onmousemove = function(ev){
        if (el.movelement) {
            el.movelement.onmousemove(ev);
            ev.stopPropagation();
        }
    }    

    
    parent.onmouseout = function(ev){

        if (!libutil.dom.checkIsParent (parent,ev.toElement,true)){
            selfremove();
            el.onmouseup();
        }
    }
    
    parent.onmouseup = function(ev){
        if (el.movelement){
            el.movelement.onmouseup();
        }
        else{
            el.onmouseup();
        }
        

    }
       
}




mainlib.get_popupbody  = function(el, width, height, remfunc){
    
    if (el.popup){
        return;
    }

    el.popup = libutil.popup.createsvgs(el,width,height,0, null, mainlib.POPUP_BODY_STYLE , null, mainlib.POPUP_R);
    
    el.popup.setAttribute('cursor', 'pointer');
    

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.setAttribute('style', 'display: none;');
        };
    }
    
    el.popup.onmouseout = function(ev){
        
        if (!libutil.dom.checkIsParent (el.popup,ev.toElement,true)){
            if (remfunc)
                    remfunc();
            else
               el.popup.setAttribute('style', 'display: none;'); 
        }
        
       
    };  

    el.popup.onmousedown= function(){
        
        if (event.target==el.popup){

         
            if (el.popup){
                
                if (remfunc)
                    remfunc();
                else
                    el.popup.setAttribute('style', 'display: none;');
                //console.profileEnd();
            }
            //console.profile(mainlib.get_popupbody.onmouseout);
        }
    }; 
      
    return el.popup.popupbody;  
}



mainlib.get_staticpopupbody  = function(el, width, height, remfunc){
    
    if (!el.popup){
    el.popup = libutil.popup.createsvgs(el,width,height,4, null , mainlib.POPUP_BODY_STYLE , 
                                        mainlib.POPUP_STATIC_STYLE , mainlib.POPUP_R);

    var mainpopup = el.popup; 
    var hoverrect = mainpopup.hoverrect;
    var btnparent = el.popup;
    var btnpos = el.popup.buttonposition;
    
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


    var rootbody = el.popup;
    
    var rootbodyreplace = function(x,y ,func){
        rootbody.style.display='none';
        setTimeout( function(){
            rootbody.setAttribute('x', x);
            rootbody.setAttribute('y', y);
            if (func ) func();
            rootbody.style.display='block';
        },10);
    }
    
    
    el.popup.rootbodyreplace=rootbodyreplace;
    
    

        
    var cteateshadowboby = function(){

        el.hoverrect = libutil.svg.create_element('rect', rootbody  , [{
            name : 'x', 
            value:  rootbody.x.baseVal.value
        },

        {
            name : 'y', 
            value:  rootbody.y.baseVal.value
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
    
        el.hoverrect.onselectstart = function(ev){
           ev.stopPropagation();
           ev.preventDefault();
           return false;}
       
        
    
    
        el.hoverrect.onmousemove = function(ev){
            if (ev.target==el.hoverrect && el.hoverrect.captured){
                if ((el.hoverrect.captured.x!=ev.x) || (el.hoverrect.captured.y!=ev.y)) {
                    var shiftX = el.hoverrect.captured.x - ev.x;
                    var shiftY = el.hoverrect.captured.y - ev.y;
                    
                    el.hoverrect.setAttribute('x', parseInt(el.hoverrect.getAttribute('x'))-shiftX );
                    el.hoverrect.setAttribute('y', parseInt(el.hoverrect.getAttribute('y'))-shiftY );
                    el.hoverrect.changerect =true;
                    el.hoverrect.captured=ev;
                }
            }
        }
    
        el.hoverrect.onmouseup = function(ev){
            if (ev.target==el.hoverrect){
                el.hoverrect.captured = undefined;                
                if (!el.hoverrect.changerect){
                    el.hoverrect.parentNode.removeChild(el.hoverrect);
                    return;
                }     
                rootbodyreplace(parseInt(el.hoverrect.getAttribute('x')),parseInt(el.hoverrect.getAttribute('y')),
                                         function(){el.hoverrect.parentNode.removeChild(el.hoverrect);} );
            }        
        }
    
        el.hoverrect.onmousedown = function(ev){
            el.hoverrect.captured = ev;
            //console.log('shadow mousedown');
            ev.stopPropagation();            
        }
        
        el.hoverrect.onmouseout = function(ev){
            if (ev.target==el.hoverrect && el.hoverrect.captured){
                el.hoverrect.onmouseup(ev);
                ev.stopPropagation();}          
        }        
    
    rootbody.parentNode.appendChild(el.hoverrect);}   

    this.closebutton.setAttributeNS(libutil.XLINK_NAMESPACE_URL, 'xlink:href', '../util/css/res/close.svg' );

    this.closebutton.onclick = function(ev){       
            if (remfunc)
                remfunc();
            else
                el.popup.parentNode.removeChild(el.popup);      
    
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
              
    el.popup.setAttribute('cursor', 'pointer');
    }
    else
    {
       el.popup.rootbodyreplace(el.popup.boundspopup.x , el.popup.boundspopup.y);
       return null;
    }    
   
    return el.popup.popupbody;  
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
    if (el.popup){
        var text = document.getElementById(el.getAttribute('id') + '_popup_sensorcalc_sensor_text');       
        if (text)
            text.textContent='';
        el.popup.setAttribute('style', '');
        return;
    }
    
    try{
        if (width<100) width=100;
   
        var body = mainlib.get_popupbody(el,width,parseFloat(width)* 2.05);
        body.setAttribute('id',el.getAttribute('id') + '_popup_body');
        
        var text = document.getElementById(el.getAttribute('id') + '_popup_sensorcalc_sensor_text');
        
        if (text)
            text.textContent='';
        
        var trpopup =document.getElementById(el.getAttribute('id') + '_popup_body');
        if (trpopup){
            trpopup.clearpopup = function(){
                el.popup.setAttribute('style', 'display: none;');
            }
        }   
            
            
        
        var defs = document.getElementById(el.getAttribute('id') + '_popup');
        
        var use = libutil.svg.create_element('use', body);
        body.useelement=use;
        use.setAttributeNS("http://www.w3.org/1999/xlink",'href','#'+el.getAttribute('id') + '_popup');
        
        
        
    }
    catch(error){
        throw error;
    }  
}

    
//gw.appendChild(btnonrect);
    
mainlib.graph_click =  function (el, nm){
    

  
    var width = mainlib.CHART_WIDTH;
    var height = mainlib.CHART_HEIGHT;
    var padding = 3;
    
    var body = mainlib.get_staticpopupbody(el,mainlib.CHART_WIDTH,mainlib.CHART_HEIGHT, function() {if (el.popup) el.popup.parentNode.removeChild(el.popup);el.popup=undefined;});
    
    if (!body && el.popup) return;
 

    body.setAttribute('id',el.getAttribute('id') + '_popup_body');
    
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
        value: width
        },
        {
        name : 'height', 
        value : height
        }]);   
    
    var html = libutil.html.create_element('html' , result);
            
    var head = libutil.html.create_element('head', html,[{
    }]);


    var htmlbody= libutil.html.create_element( 'body' ,html, [{name: 'style', value: 'margin: 0; padding: '+ padding + 'px'}]);
            
    var bodydiv= libutil.html.create_element('div' , htmlbody, [{name : 'id' , value: el.getAttribute('id') + '_popup_graph'},
                                                                 {name: 'style' , value: '-webkit-user-select: none'}] );
     
    var script = libutil.html.create_element('script', head );

    script.textContent="new libutil.trendchart('"+el.getAttribute('id') + '_popup_graph'+"','"+
                                                         el.getAttribute('id') + '_popup_body'+
                                                         "', "+"['"+nm+"'], 600, ['red','green','blue','#880'], " + 
                                                         (width - 2* padding) + ", " + (height - 2* padding)+")";
    
        
    

}



    
    
    

