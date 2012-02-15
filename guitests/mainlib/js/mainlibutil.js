
var mainlibutil = {};

mainlibutil.startup = {};

mainlibutil.window = {};

mainlibutil.svg = {};

mainlibutil.html = {};

mainlibutil.dom = {};

mainlibutil.www = {};

mainlibutil.document = {};

mainlibutil.designtime = {};

mainlibutil.global = {};


function dvnci_open(name){
    if (dvnci_iseditable()) return;
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (!fl[i].window){
                    var win=window.open(fl[i]['path'],fl[i]['name'],fl[i]['param'].toString());
                    fl[i].window=win;
                }
                else{
                    fl[i].window.focus();  
                }
                return;
            }
        }
    }
}

function dvnci_close(name){
    if (dvnci_iseditable()) return;
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


function dvnci_open_design(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (!fl[i].window){
                    var win=window.open(fl[i]['path'],fl[i]['name'],fl[i]['param'].toString());
                    fl[i].window=win;
                }
                else{
                    fl[i].window.focus();  
                }
                return;
            }
        }
    }
}

function dvnci_close_design(name){
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

function exit(){
    if (dvnci_iseditable()) return;
    dvnci_exit();
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

//

mainlibutil.startup.init = function(){
    var el = document; 
    if (dvnci_iseditable()){
        document.red = new redactor(document);
        mainlibutil.designtime.getObjectInspector();
        mainlibutil.designtime.getMainWindow();
        mainlibutil.designtime.getFormInspector();
       }
    window.onunload=dvnci_close_win;
}

//  window

mainlibutil.window.create = function(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal){
    var tmp='caption=' + ( caption ? caption :  "") +
       ',left='+ (left ? left : '0') +
       ',top=' + (top ? top : '0') +
       ',width=' + (width ? width : '200px') +
       ',height=' + (height ? height : '200px') +
       ',tooltip=' + (tooltip ? 'yes' : '0') +
       ',allwaystop='+ (allwaystop ? 'yes' : '0') +
       (nodecorate ? ',decorated=no' : '') +
       ';'
    return window.open('', name , tmp);
}


mainlibutil.window.createhtml = function(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, stylefile, style){
    var newwin=mainlibutil.window.create(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal);
    newwin.document.open();
    newwin.document.write('<?xml version="1.0" encoding="UTF-8"?>');
    newwin.document.write('<html>');
    newwin.document.write('    <head>');
    newwin.document.write('     <script type="text/javascript" src="../mainlib/js/startup.js"></script>');
    newwin.document.write('     <script type="text/javascript" src="../mainlib/js/redactor.js"></script>');
    newwin.document.write('     <script type="text/javascript" src="../mainlib/js/mainlibutil.js"></script>');
    if (stylefile)
        newwin.document.write('     <link rel="stylesheet" type="text/css" href="'+stylefile+'">');
    if (style)
        newwin.document.write(style);
    newwin.document.write('    </head>');
    newwin.document.write('    <body>');
    newwin.document.write('    </body>')
    newwin.document.write('</html>');
    newwin.document.close();
    return newwin;
    
}

//


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


///  Main Window

mainlibutil.designtime.getMainWindow = function (){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.maindesignwin){
        var maindesignwin=mainlibutil.window.createhtml('_mainDesign','Редактор','5%','5%', '600','60','yes','yes',null,null, "../mainlib/css/maindesignwindow.css");
        tmp.maindesignwin=maindesignwin;
        tmp.maindesigndoc=maindesignwin.document;
        maindesignwin.onunload=mainlibutil.designtime.destroyMainWindow;
        var objdoc =maindesignwin.document;
        try{
          var body=objdoc.getElementsByTagName('body')[0];
          var div = mainlibutil.html.create_div(body);
          div.setAttribute('id','toolbar');
          var btn1 = mainlibutil.html.create_button( div,null,'toolbar-item toggleable','',function() {dvnci_exit();});
          mainlibutil.html.create_div(btn1,null,'toolbar-icon');
          var btn2 = mainlibutil.html.create_button( div,null,'toolbar-item toggleable','',function() {dvnci_exit();});
          mainlibutil.html.create_div(btn2,null,'toolbar-icon');
          
        }
        catch(error){
           alert ('Create window error:' + error);
           return null;
        }       
    }   
    return (tmp && tmp.maindesignwin) ? tmp.maindesignwin : null;
}


mainlibutil.designtime.destroyMainWindow = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.maindesignwin)
        tmp.maindesignwin=undefined;
    if (tmp && tmp.maindesigndoc)
        tmp.maindesigndoc=undefined;   
    dvnci_exit();
       
    
}

///  Object inspector

mainlibutil.designtime.getObjectInspector = function (){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.objectinspectorwin){
 
        var objectinspectorwin=mainlibutil.window.createhtml('_ObjectInspector','Свойства','15%','15%', '400','650','yes','yes',null,null, "../mainlib/css/objectinspector.css");
        tmp.objectinspectorwin=objectinspectorwin;
        tmp.objectinspectordoc=objectinspectorwin.document;
        objectinspectorwin.onunload=mainlibutil.designtime.destroyObjectInspector;
        var objdoc =objectinspectorwin.document;
        try{
          var body=objdoc.getElementsByTagName('body')[0];
          var div = mainlibutil.html.create_div(mainlibutil.html.create_div(body),null,"scrollWrapper");
          var table = mainlibutil.html.create_table(div,null,"scrollable");
          var tbody = mainlibutil.html.create_tbody(table);
          var tr = mainlibutil.html.create_tr(tbody);
          var th1 =mainlibutil.html.create_th(tr);
          th1.innerHTML='Имя';
          var th2 =mainlibutil.html.create_th(tr);
          th2.innerHTML='Значение';
          tmp.objectinspectortbody=tbody;
        }
        catch(error){
           alert ('Create window error:' + error);
           return null;
        }       
    }   
    return (tmp && tmp.objectinspectorwin) ? tmp.objectinspectorwin : null;
}

mainlibutil.designtime.getObjectInspectorDocument = function(){
    var tmp = mainlibutil.global.getGlobal();
    if (tmp && tmp.objectinspectordoc) {
        return tmp.objectinspectordoc; 
    }
}

mainlibutil.designtime.getObjectInspectorTbody = function(){
    var tmp = mainlibutil.global.getGlobal();
    if (tmp && tmp.objectinspectortbody) {
        return tmp.objectinspectortbody;       
    }   
}  


mainlibutil.designtime.showObjectInspector = function(){
    var tmp = mainlibutil.designtime.getObjectInspector();
    if (tmp)
        tmp.focus();
}



mainlibutil.designtime.closeObjectInspector = function(){
    var tmp = mainlibutil.designtime.getObjectInspector();
    if (tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
}

mainlibutil.designtime.destroyObjectInspector = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.objectinspectorwin)
        tmp.objectinspectorwin=undefined;
    if (tmp && tmp.objectinspectordoc)
        tmp.objectinspectordoc=undefined;
    if (tmp && tmp.objectinspectortbody)
        tmp.objectinspectortbody=undefined;   
    
}


// Form inspector


mainlibutil.designtime.getFormInspector = function (){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.forminspectorwin){
 
        var forminspectorwin=mainlibutil.window.createhtml('_FormInspector','Окна','65%','65%', '300','400','yes','yes',null,null, "../mainlib/css/forminspector.css");
        tmp.forminspectorwin=forminspectorwin;
        tmp.forminspectordoc=forminspectorwin.document;
        forminspectorwin.onunload=mainlibutil.designtime.destroyFormInspector;
        var objdoc =forminspectorwin.document;
        try{
          var body=objdoc.getElementsByTagName('body')[0];
          var div = mainlibutil.html.create_div(mainlibutil.html.create_div(body),null,"scrollWrapper");
          var table = mainlibutil.html.create_table(div,null,"scrollable");
          var tbody = mainlibutil.html.create_tbody(table);
          var tr = mainlibutil.html.create_tr(tbody);
          var th1 =mainlibutil.html.create_th(tr);
          th1.innerHTML='id';
          var th2 =mainlibutil.html.create_th(tr);
          th2.innerHTML='Путь';
          var th3 =mainlibutil.html.create_th(tr);
          th3.innerHTML='O';
          var th4 =mainlibutil.html.create_th(tr);
          th4.innerHTML='X';
          tmp.forminspectortbody=tbody;
        }
        catch(error){
           alert ('Create window error:' + error);
           return null;
        }       
    }   
    mainlibutil.designtime.fillFormInspector();
    return (tmp && tmp.forminspectorwin) ? tmp.forminspectorwin : null;
}

mainlibutil.designtime.fillFormInspector = function (){
    var tbody = mainlibutil.designtime.getFormInspectorTbody();
    mainlibutil.dom.clearChildNode(tbody);   

    var tr = mainlibutil.html.create_tr(tbody);
    var th1 =mainlibutil.html.create_th(tr);
    th1.innerHTML='id';
    var th2 =mainlibutil.html.create_th(tr);
    th2.innerHTML='Путь';
    var th3 =mainlibutil.html.create_th(tr);
    th3.innerHTML='O';
    var th4 =mainlibutil.html.create_th(tr);
    th4.innerHTML='X';
    
    
    var fl= mainlibutil.global.getFormList();

    
                            
    for (var i=0; i<fl.length; ++i ){
        var formname=fl[i]['name'];
        formname=formname.toString();
        var tr= mainlibutil.html.create_tr(tbody);
       
        var td1= mainlibutil.html.create_td(tr);
        td1.innerHTML=formname;
        
        td1.className='static';
   
        var td2= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var val=fl[i]['path'];
        td2.innerHTML= val ? val : "";
        
        var td3= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btno = mainlibutil.html.create_button( td3,null,null,'O');
        btno.setAttribute('onclick','dvnci_open_design("'+formname+ '");');
        
        var td4= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btnc = mainlibutil.html.create_button( td4,null,null,'X');
        btnc.setAttribute('onclick','dvnci_close_design("'+formname+ '");');
    
}
        
        
}

mainlibutil.designtime.getFormInspectorDocument = function(){
    var tmp = mainlibutil.global.getGlobal();
    if (tmp && tmp.forminspectordoc) {
        return tmp.forminspectordoc; 
    }
}

mainlibutil.designtime.getFormInspectorTbody = function(){
    var tmp = mainlibutil.global.getGlobal();
    if (tmp && tmp.forminspectortbody) {
        return tmp.forminspectortbody;       
    }   
}  


mainlibutil.designtime.showFormInspector = function(){
    var tmp = mainlibutil.designtime.getFormInspector();
    if (tmp)
        tmp.focus();
}



mainlibutil.designtime.closeFormInspector = function(){
    var tmp = mainlibutil.designtime.getFormInspector();
    if (tmp.forminspectorwin)
        tmp.forminspectorwin.close();
}

mainlibutil.designtime.destroyFormInspector = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.forminspectorwin)
        tmp.forminspectorwin=undefined;
    if (tmp && tmp.forminspectordoc)
        tmp.forminspectordoc=undefined;
    if (tmp && tmp.forminspectortbody)
        tmp.forminspectortbody=undefined;   
    
}






  

    
