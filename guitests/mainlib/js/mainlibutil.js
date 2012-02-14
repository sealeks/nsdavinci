
var mainlibutil = {};

mainlibutil.startup = {};

mainlibutil.svg = {};

mainlibutil.html = {};

mainlibutil.dom = {};

mainlibutil.www = {};

mainlibutil.document = {};

mainlibutil.designtime = {};

mainlibutil.global = {};


function dvnci_open(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (!fl[i].window){
                  var win=window.open(fl[i]['path'],fl[i]['name'],fl[i]['param'].toString());
                  fl[i].window=win;}
                else{
                  fl[i].window.focus();  
                }
                return;
            }
        }
    }
}

function dvnci_close(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (fl[i].window)
                    fl[i].window.close();
                fl[i].window=null;
                return;
            }
        }
    }
}

function dvnci_close_win(){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i].window==window){
                fl[i].window=null;
                return;
            }
        }
    }
}


//

mainlibutil.global.getGlobal = function (){
    return window.dvnci_globalobject();
}

mainlibutil.global.getFormList = function (){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.formlist)
        tmp.formlist=[];
    return (tmp && tmp.formlist) ? tmp.formlist : null;
}

mainlibutil.global.getObjectInspector = function (){
 var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.objectinspectorwin){
        var objectinspectorwin=window.open('', '' , 'caption=Свойства,left=5%,top=5%, width=400,height=650,tooltip=yes,allwaystop=yes;');
        tmp.objectinspectorwin=objectinspectorwin;
        objectinspectorwin.onclose=mainlibutil.designtime.destroyObjectInspector;
        objectinspectorwin.document.open();    
         var style='<style type="text/css"> body { margin: 0 0; padding: 0 0; -webkit-user-select: none;}'+
        'div.scrollHeader{'+  
        'margin: 0 0; padding: 0 0; border-top-right-radius: 6px; border-top-left-radius: 6px;'+
        'border:  1px solid #000022; background: #000044; color: yellow; padding: 4px; -webkit-user-select: none;}'+  
                
        'div.scrollWrapper{'+
                
        'overflow:scroll; margin: 0 0; padding: 0 0;'+
        'border:  1px solid grey; height:99%;}'+
                
        'table.scrollable{'+
        'border-collapse:collapse;'+
        'text-align: left;'+
        'font-size: 12px;'+
        'background:#f0f0f0;'+
        '}'+
        'table.scrollable th{'+
        'border: 1px solid #999999;'+
        'background:#e0e0e0;'+
        'position: relative;'+
        'padding-left: 6px;'+
        'background-position: 100% 100%;'+
        '}'+
        'table.scrollable tbody{'+
        'overflow:auto;'+
        'border-spacing: 0px'+
        '}'+
        'table.scrollable td.static{ background: -webkit-gradient(linear, left top, left bottom, from(#eee), to(#aaa));'+
        'border: 1px solid gray; '+
        'padding: 0px 0px;'+
        '}' +
        'table.scrollable td{'+
        'border: 1px solid gray; '+
        'padding: 0px 0px;'+
        '}' +
        'table.scrollable td input{'+
        'display: block; width: 100%; border: 0px; color: black;'+
        'padding: 0px 0px; font-size: 12px; '+
        '}' +
        'table.scrollable td select{'+
        'display: block; width: 100%; border: 0px; color: black;'+
        'padding: 0px 0px; font-size: 12px;'+
        '}' +
        '.diffvalue{'+
        'background: #808080;'+
        '}</style>';                
        objectinspectorwin.document.write('<?xml version="1.0" encoding="UTF-8"?>');
        objectinspectorwin.document.write('   <html>');
        objectinspectorwin.document.write('      <head>');
        objectinspectorwin.document.write('<script type="text/javascript" src="../mainlib/js/startup.js"></script>');
        objectinspectorwin.document.write('<script type="text/javascript" src="../mainlib/js/redactor.js"></script>');
        objectinspectorwin.document.write('<script type="text/javascript" src="../mainlib/js/mainlibutil.js"></script>');
        objectinspectorwin.document.write(style);
        objectinspectorwin.document.write('   </head>');
        objectinspectorwin.document.write('   <body>');
        objectinspectorwin.document.write('   <div>');
        objectinspectorwin.document.write('   <div class="scrollWrapper">');
        objectinspectorwin.document.write('   <table class="scrollable" width="100%">');
        objectinspectorwin.document.write('   <tbody>');
        objectinspectorwin.document.write('   <tr>');
        objectinspectorwin.document.write('   <th> Свойство');
        objectinspectorwin.document.write('   </th>');       
        objectinspectorwin.document.write('   <th> Значение');
        objectinspectorwin.document.write('   </th>');
        objectinspectorwin.document.write('   </tr>');       
        objectinspectorwin.document.write('   </tbody>');
        objectinspectorwin.document.write('   </table>');
        objectinspectorwin.document.write('   </div>');       
        objectinspectorwin.document.write('   </div>');        
        objectinspectorwin.document.write('   </body>');
        objectinspectorwin.document.write('   </html>');
        objectinspectorwin.document.close();
        objectinspectorwin.onunload=mainlibutil.designtime.destroyObjectInspector;
        }
        
       
    return (tmp && tmp.objectinspectorwin) ? tmp.objectinspectorwin : null;
}


//

mainlibutil.startup.init = function(){
    var el = document; 
    if (dvnci_iseditable()){
    //document.addEventListener('keyup' ,function () {
        //if ((event.keyCode==82) && (event.shiftKey)) {
            //mainlibutil.designtime.initAll();
            document.red = new redactor(document);
            //postMessage("t","file://");
            //event.stopPropagation();
            //event.preventDefault();
           // return;
       // }      
    //});
    }
    //window.addEventListener("message", function () { alert(window.name);},false);
    window.onunload=dvnci_close_win;
}


mainlibutil.html.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS('http://www.w3.org/1999/xhtml', name);
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_html = function (parent, style){  
    var newel = mainlibutil.html.create('html', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    return newel;
}


mainlibutil.html.create_head = function (parent, style){  
    var newel = mainlibutil.html.create('head', parent);
    if (!newel) return;
    if (parent) parent.appendChild(newel);
    if (style) 
        mainlibutil.html.create_style(newel, style)
    return newel;
}

mainlibutil.html.create_body = function (parent, style, classnm){
    var newel = mainlibutil.html.create('body', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_tbody = function (parent, style, classnm){
    var newel = mainlibutil.html.create('tbody', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_table = function (parent, style, classnm){
    var newel = mainlibutil.html.create('table', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}


mainlibutil.html.create_th = function (parent, style, classnm){
    var newel = mainlibutil.html.create('th', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_tr = function (parent, style, classnm){
    var newel = mainlibutil.html.create('tr', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_td = function (parent, style, classnm){
    var newel = mainlibutil.html.create('td', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_div = function (parent, style, classnm){
    var newel = mainlibutil.html.create('div', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_span = function (parent, style, classnm){
    var newel = mainlibutil.html.create('span', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}



mainlibutil.html.create_style = function (parent,  style){
    
    var newel = mainlibutil.html.create('style', parent);
    if (!newel) return;
    newel.setAttribute('type', 'text/css' );
    if (style) newel.innerHTML=style;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_button = function (parent, style, classnm, name, onclickfunc){
    var newel = mainlibutil.html.create('button', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (name) newel.innerHTML=name;
    if (onclickfunc) newel.onclick=onclickfunc;
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.html.create_input = function (parent, type, value){
    var newel = mainlibutil.html.create('input', parent);
    if (!newel) return;
    if (type) newel.setAttribute('type', type );
    if (value) {
        newel.setAttribute('value', value );
        newel.innerHTML=value;
    }
    return newel;
}

///////////////////////////////////////////////

mainlibutil.dom.clearChildNode = function (element){
    while (element.hasChildNodes()) 
        element.removeChild(element.lastChild);
}


///////////////////////////////////////////////



mainlibutil.svg.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS('http://www.w3.org/2000/svg', name);
    if (parent) parent.appendChild(newel);
    return newel;
}

mainlibutil.svg.create_svg = function (parent, x, y,  height, width, view){
    
    var newel = mainlibutil.svg.create('svg', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));
    if (width || width==0) newel.setAttribute('width', parseFloat(width));
    if (height || height==0) newel.setAttribute('height', parseFloat(height));    
    if (view) newel.setAttribute('viewBox', view);
    return newel;
}


mainlibutil.svg.create_rect = function (parent, x, y,  height, width,  rx, ry, style, classnm){
    
    var newel = mainlibutil.svg.create('rect', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));
    if (width || width==0) newel.setAttribute('width', parseFloat(width));
    if (height || height==0) newel.setAttribute('height', parseFloat(height));    
    if (rx) newel.setAttribute('rx', parseFloat(rx));
    if (ry) newel.setAttribute('ry', parseFloat(ry));
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.setAttribute('class', classnm);
    return newel;
}

mainlibutil.svg.create_circle = function (parent, x, y,  r,  style, classnm){
    
    var newel = mainlibutil.svg.create('circle', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('cx', parseFloat(x));
    if (y || y==0) newel.setAttribute('cy', parseFloat(y));
    if (r || r==0) newel.setAttribute('r', parseFloat(r));
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.setAttribute('class', classnm);
    return newel;
}

mainlibutil.svg.create_text = function (parent, x, y,  style, classnm, text){
    
    var newel = mainlibutil.svg.create('text', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));  
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.setAttribute('class', classnm);
    if (text){
          var textdat = parent.ownerDocument.createTextNode('R');    
          newel.appendChild(textdat);
    }
    return newel;
}

mainlibutil.svg.create_foreignObject = function (parent, x, y, height, width){
    
    var newel = mainlibutil.svg.create('foreignObject', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));
    if (width || width==0) newel.setAttribute('width', parseFloat(width));
    if (height || height==0) newel.setAttribute('height', parseFloat(height));
    
    return newel;
}

mainlibutil.svg.foriegn_text = function (parent, x, y, height, width, text, style){
    
    var newel = mainlibutil.svg.create_foreignObject(parent, x, y, height, width);
    
    var body = mainlibutil.html.create_body(newel, 'margin: 0px; padding: 50px; height: '+height+'px');
    
    var div = mainlibutil.html.create_div(body, style);
    
    var span = mainlibutil.html.create_span(div, 'padding: 50px; ');
    
    var headertextnode=parent.ownerDocument.createTextNode(text);
    
    span.appendChild(headertextnode);
    

}


mainlibutil.svg.create_header = function (parent, x, y,  height, width, rx, ry,  rectstyle, text, htmltextstyle){

    var newheadrect =  mainlibutil.svg.create_rect( parent, 
        x, y,  height, width, rx , ry, rectstyle);


    
    newheadrect.onmouseout = function() {
        event.preventDefault();
        event.stopPropagation();
        return;
    } 
        
    
    var headersvg=mainlibutil.svg.create_svg(parent, 
        x,y, height, width);
   
   

    var headertext=mainlibutil.svg.foriegn_text(headersvg,0,0, height, width,text,
        htmltextstyle);
    
    return newheadrect;
    
}

mainlibutil.svg.create_button = function (parent, x, y,  height, width, rx, ry,  rectstyle, rectclass,   text, textstyle){

    var headersvg=mainlibutil.svg.create_svg(parent, 
        x,y, height, width);   

    var newheadrect =  mainlibutil.svg.create_rect( headersvg, 
        0, 0,  height, width, rx , ry,  rectstyle, rectclass);
                                       
    headersvg.onmouseout = function() {
        event.preventDefault();
        event.stopPropagation();
        return;
    }                                        
                                       
                                
                                       
    var headertext=mainlibutil.svg.create_text(headersvg,
        width / 2, height / 2, 
        textstyle,
        'central_svgnatext');

    
    var headertextnode=parent.ownerDocument.createTextNode(text);
    
    headertext.appendChild(headertextnode);
    
    return headersvg;                                    

    
}


mainlibutil.www.createWindow = function(doc, id, x, y, width, height, style){
    
    if (!doc) return undefined;

    var result = undefined; 
      

    if (doc){
        var root = doc.documentElement;
        if (root) {
     
            var result = mainlibutil.svg.create_foreignObject(doc.documentElement,  x ? x : 0, y ? y : 0, height ? height : 300, width ? width : 300 );
            result.setAttribute('opacity', '0.9');
            result.setAttribute('id',id);
            
            var html = mainlibutil.html.create_html(result);
            
            mainlibutil.html.create_head(html,style);
            
            var body= mainlibutil.html.create_body(html);
            
            var bodydiv= mainlibutil.html.create_div(body);
           
            var divhd= mainlibutil.html.create_div(bodydiv, null, 'scrollHeader');
            divhd.setAttribute('id', id+'_header');
            divhd.innerHTML=id;

            result.divhd = divhd;
            
            result.bindelement=bodydiv;
               
            return result;

        }
    }
    return undefined;
}


mainlibutil.document.readDoc = function (url){ 
    try{
        var xmlHttp=new XMLHttpRequest();
        xmlHttp.open("GET",url,false);
        xmlHttp.send(null);
        return xmlHttp.responseXML;
    }
    catch(exception){
    }
    return null;
}


mainlibutil.document.writeDoc = function (doc){
    if (doc && dvnci_writefile){
        var xmls = new XMLSerializer();  
        var data= xmls.serializeToString(doc); 
        dvnci_writefile(doc.baseURI,data);
    }
}

// radactor util

mainlibutil.designtime.getObjectInspectorDocument = function(){
    var tmp = mainlibutil.global.getObjectInspector();
    return tmp ? tmp.document : undefined;
}

mainlibutil.designtime.showObjectInspector = function(){
    var tmp = mainlibutil.global.getObjectInspector();
    if (tmp)
        tmp.focus();
}

mainlibutil.designtime.closeObjectInspector = function(){
    var tmp = mainlibutil.global.getObjectInspector();
    if (tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
}

mainlibutil.designtime.destroyObjectInspector = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.objectinspectorwin){
        tmp.objectinspectorwin=undefined;
    }
}


mainlibutil.designtime.getObjectInspector = function(){
    var tmp = mainlibutil.global.getObjectInspector();
    var doc = mainlibutil.designtime.getObjectInspectorDocument();
    if (tmp && doc) {
          return doc.getElementsByTagName('tbody')[0];       
    }
    
}    
    
mainlibutil.designtime.initAll = function(){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i].window && fl[i].window.document){
                //fl[i].window.document.red = new redactor(fl[i].window.document);
                postMessage("t");

            }
        }
    }
}    

mainlibutil.designtime.uninitAll = function(){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i].window){
            }
        }
    }
}  
    
