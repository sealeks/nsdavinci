var mainlib = {    
    
};

mainlib.NAMESPACE_URL = 'http://dvnci/mlib';

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

    el.popup = libutil.popup.createsvgs(el,width,height,0, null, 'fill: #333; opacity: 0.5; ', null, 10);
    
    el.popup.setAttribute('cursor', 'pointer');
    

    
    if (el.popup.firstChild) {
        el.popup.firstChild.onclick= function(){
            el.popup.setAttribute('style', 'display: none;');
        };
    }
    
    el.popup.onmouseout = function(ev){
        
        if (!libutil.dom.checkIsParent (el.popup,ev.toElement,true)){
            //console.profile('mainlib.get_popupbody.onmouseout');
            
            //console.profileEnd('mainlib.get_popupbody.onmouseout');
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
    
     //if (el.popup){
       
        //el.popup.setAttribute('style', '');
      //  return;
  //  }
  
    var width = 400;
    var height = 200;
    var padding = 3;
    
 
    var body = mainlib.get_popupbody(el,400,200, function() { if (el.popup) el.popup.parentNode.removeChild(el.popup); el.popup=undefined; });

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

    //libutil.html.create_element('script', head , [{ name: 'type' , value: "text/javascript"}, { name: 'src' , value: "../util/js_ext/hightchart/highcharts.js"}]);
    //libutil.html.create_element('script', head , [{ name: 'type' , value: "text/javascript"}, { name: 'src' , value: "../util/js_ext/hightchart/jquery.min.js"}]);



            
    var htmlbody= libutil.html.create_element( 'body' ,html, [{name: 'style', value: 'margin: 0; padding: '+ padding + 'px'}]);
            
    var bodydiv= libutil.html.create_element('div' , htmlbody, [{ name : 'id' , value: el.getAttribute('id') + '_popup_graph'}] );
    
    var script = libutil.html.create_element('script', head );
    script.textContent="test = new libutil.trendchart('"+el.getAttribute('id') + '_popup_graph'+
        "',['"+nm+"'], 600, ['red','green','blue','#880'], " + (width - 2* padding) + ", " + (height - 2* padding)+")";
    
        
    
    return;
    
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


    
    
    


