
var mainlibutil = {};

mainlibutil.util = {};

mainlibutil.startup = {};

mainlibutil.project = {};

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
                    win.document.domain=document.domain;
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
                if (fl[i].window){
                    fl[i].window.onunload=null;
                    fl[i].window.close();
                }
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


function init_project_controller(){
    mainlibutil.global.getStartupDoc(document);   
    mainlibutil.project.init_form();
    if (dvnci_iseditable()) {
        mainlibutil.designtime.getMainWindow();
        mainlibutil.designtime.getLibInspector(true);
    }

}

//




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

mainlibutil.global.getLibList = function (){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.liblist)
        tmp.liblist=[];
    return (tmp && tmp.liblist) ? tmp.liblist : null;
}

mainlibutil.global.getStartupDoc = function (doc){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.startupdocument && doc)
        tmp.startupdocument=doc;
    return (tmp && tmp.startupdocument) ? tmp.startupdocument : null;
}

//

mainlibutil.startup.init = function(){
    var el = document; 
    window.addEventListener('message', function (ev) {
        window.close();
    }, false);
    if (dvnci_iseditable()){
        document.red = new redactor(document);
        mainlibutil.startup.initredactor(window.name, document.red);

    }
    window.onunload=dvnci_close_win;
}

mainlibutil.startup.initredactor = function(name, red){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                fl[i].red=red;
                return;
            }
        }
    }
}


//  project

mainlibutil.project.init_form = function(){
    var doc = mainlibutil.global.getStartupDoc();
    if (doc){
        try{
            var elp=doc.getElementsByTagName('project')[0];
            var projectPath=elp.getAttribute('path');
            
            var els=doc.getElementsByTagName('form');
            var fl=mainlibutil.global.getFormList();
                      
            var ellib=doc.getElementsByTagName('lib');
            var ll=mainlibutil.global.getLibList();
            
            
            if (els){
                for (var i=0; i<els.length;++i){
                    var path = projectPath && els[i].getAttribute('file') ? projectPath.toString() + els[i].getAttribute('file').toString() : 
                    els[i].getAttribute('file') ? els[i].getAttribute('file').toString() : null; 
                    if (path){   

                        var param = mainlibutil.project.buildparam(els[i]);
                        var win=window.open(path,
                            els[i].getAttribute('name')  ? els[i].getAttribute('name') :  '',
                            param ? param : '');
                        win.document.domain=document.domain;     
                    
                        fl.push({
                            'name' : els[i].getAttribute('name'),
                            'file' : els[i].hasAttribute('file') ? els[i].getAttribute('file') : '',
                            'path'  : path,
                            'param'  : param,
                            'window'  : win,
                            'top'  : els[i].hasAttribute('top') ? els[i].getAttribute('top') : null,
                            'left'  : els[i].hasAttribute('left') ? els[i].getAttribute('left') : null,
                            'width'  : els[i].hasAttribute('width') ? els[i].getAttribute('width') : null,
                            'height'  : els[i].hasAttribute('height') ? els[i].getAttribute('height') : null,
                            'caption'  : els[i].hasAttribute('caption') ? els[i].getAttribute('caption') : '',
                            'decorated'  : els[i].hasAttribute('decorated') ? els[i].getAttribute('decorated') : true,
                            'resizable'  : els[i].hasAttribute('resizable') ? els[i].getAttribute('resizable') : null,
                            'modal'  : els[i].hasAttribute('modal') ? els[i].getAttribute('modal') : null,
                            'allwaystop'  : els[i].hasAttribute('allwaystop') ? els[i].getAttribute('allwaystop') : null,
                            'visible'  : ((els[i].hasAttribute('visible')) && (els[i].getAttribute('visible')=='false')) ? false : true,
                            'element' : els[i]
                        });
                    }         
                }
            }
                
            if (ellib){       
                for (var i=0; i<ellib.length;++i){
                    if (ellib[i].hasAttribute('xsd')){
                        ll.push({
                            'name' : ellib[i].hasAttribute('name') ? ellib[i].getAttribute('name') : ('unnamed'+i),
                            'path' : ellib[i].getAttribute('xsd'),
                            'components' : mainlibutil.project.set_components(ellib[i].getAttribute('xsd'))
                        })
                    }
                }
                }
        
        
    }
    catch(error){ 
        alert('Startup error: '+ error)
    }
}
}


mainlibutil.project.set_components = function(path){
    var result = [];
    var doc = mainlibutil.document.readDoc(path);
    if (doc){
        var els = doc.getElementsByTagNameNS('../dvnlib.xsl','creator');        
        for (var i=0; i<els.length;++i){
            result.push({ 
                'name' : els[i].hasAttribute('name') ? els[i].getAttribute('name') : ('unnamed'+i),
                'hint' : els[i].hasAttribute('hint') ? els[i].getAttribute('hint') : null,
                'text' : els[i].textContent,
                'element' : els[i].firstElementChild
            });
        }
    }
    return result;   
}

mainlibutil.project.get_components = function(tool, name){
    var ll=mainlibutil.global.getLibList();
    if (ll){
        for (var i=0; i<ll.length;++i){
            if (ll[i].name==tool){
                var comps = ll[i].components;
                for (var j=0; j<comps.length;++j){
                    if (comps[j].hint==name){
                        return comps[j].element;
                    }
                }
            }
        }
    }
    return null;   
}

mainlibutil.project.getFormInfo = function(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                return fl[i];
            }
        }
    }
    return null;        
}

mainlibutil.project.buildparam = function(el){
    if (el){
        var param='';
        if (el.getAttribute('caption'))
            param=param+";caption="+el.getAttribute('caption');
        if (el.getAttribute('left'))
            param=param+";left="+el.getAttribute('left');
        if (el.getAttribute('top'))
            param=param+";top="+el.getAttribute('top');  
        if (el.getAttribute('width'))
            param=param+";width="+el.getAttribute('width');
        if (el.getAttribute('height'))
            param=param+";height="+el.getAttribute('height'); 
        if (el.getAttribute('decorated') && ((el.getAttribute('decorated')=='no') || (el.getAttribute('decorated')=='0')))
            param=param+";decorated=no";
        if (el.getAttribute('allwaystop') && ((el.getAttribute('allwaystop')=='yes') || (el.getAttribute('decorated')=='1')))
            param=param+";allwaystop=yes";
        if (el.getAttribute('resizable') && ((el.getAttribute('resizable')=='no') || (el.getAttribute('resizable')=='0')))
            param=param+";resizable=no";
        if (el.getAttribute('modal') && ((el.getAttribute('modal')=='yes') || (el.getAttribute('modal')=='1')))
            param=param+";modal=yes";    
        if (el.getAttribute('state'))
            param=param+";state="+el.getAttribute('state');

        return param;                
    }
    return '';
    
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

mainlibutil.html.create_tabel_header = function (tr, style, classnm, arr){
    for (var i=0; i < arr.length; ++i){
        var th = mainlibutil.html.create_th(tr, style, classnm);
        th.innerHTML=arr[i];
    } 
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

mainlibutil.html.create_select = function (parent, type, value, list, addit){
    var newel = mainlibutil.html.create('select', parent);
    if (!newel) return;
    if (type)
        newel.setAttribute('type', type );
    if (value) 
        newel.setAttribute('value', value );

    var newop = mainlibutil.html.create('option', newel);
    //newop.setAttribute('value', value );
    newop.setAttribute('selected','');
    newop.innerHTML=value;

    for(var i=0; i < list.length; i++){
        if (list[i]!=value){
            var newop = mainlibutil.html.create('option', newel);
            //newop.setAttribute('value', list[i] );
            newop.innerHTML=list[i];
        }

    }

    if (addit){
        var newop = mainlibutil.html.create('option', newel);
        newop.setAttribute('value', '...' );
        newop.innerHTML='...';
    }
    return newel;
}

mainlibutil.html.create_tool = function (doc, nametool, names, funcs, size){
    if (names){
    var body=doc.getElementsByTagName('body')[0];
    var result = {};
    if (body) {
        mainlibutil.html.create_tool_style(doc, nametool, names,  size);
        var div = mainlibutil.html.create_div(body);
        div.setAttribute('id','toolbar');
        for (var i=0;i<names.length;++i){
            var btn = mainlibutil.html.create_button( div,null,nametool+'-item toggleable '+names[i],'', (funcs && funcs.length > i) ? funcs[i] : null);
            btn.namebtn=names[i];
            btn.nametool=nametool;
            mainlibutil.html.create_div(btn,null,nametool+'-icon')
            result[names[i]] = btn;
        } 
        return result;
    }}
   return undefined;
} 



mainlibutil.html.create_tool_style = function (doc, nametool, names,  sz){
    var head = doc.getElementsByTagName('head')[0];
    if (head){
        var onfile = nametool + 'on';
        var offfile = nametool + 'off';
        var disablefile = nametool + 'dsbl';
        var size = sz ? sz + "px" : "30px";
        
        var style="."+nametool+"-label {\n"+             
        " color: rgba(18,50,114,1) !important;\n"+             
        " text-shadow: none;}\n"+
        " \n"+

        "."+nametool+"-item {\n"+
        " margin: 0;\n"+
        " padding: 0 6px;\n"+
        " background-color: transparent;\n"+
        " border-style: none;\n"+
        " border-color: transparent;}\n"+
        " \n"+


        "."+nametool+"-item.toggleable {\n"+
        " padding-top: 4px;}\n"+
        " \n"+

        "."+nametool+"-icon {\n"+
        " display: inline-block;\n"+
        " width: "+ size+";\n"+
        " height: "+ size+";\n"+
        " background-image: url(../mainlib/css/res/"+onfile+".png);}\n"+
        " \n"+
                  
        "."+nametool+"-item[disabled] ."+nametool+"-icon{\n"+
        " background-image: url(../mainlib/css/res/"+disablefile+".png);}\n"+
        " \n"+

        "."+nametool+"-item:hover[disabled] ."+nametool+"-icon{\n"+
        " background-image: url(../mainlib/css/res/"+disablefile+".png);}\n"+
        " \n"+

        "."+nametool+"-item[off] ."+nametool+"-icon{\n"+
        " background-image: url(../mainlib/css/res/"+offfile+".png);}\n"+
        " \n"+


        "."+nametool+"-item:active ."+nametool+"-icon {\n"+
        " background-position-y: "+ size+";}\n"+
        " \n"+

        "."+nametool+"-item:hover ."+nametool+"-icon {\n"+
        " background-position-y: "+ size+";\n"+
        " border-style: 1px;\n"+
        " border-color: red;}\n"+
        " \n"+


        "."+nametool+"-item.toggleable:active ."+nametool+"-label {\n"+
        " text-shadow: none;}\n"+
        " \n";

             
        for (var i=0;i<names.length;++i){
            var vsize = sz ? ("-" + sz*i + "px") : ("-" + 30*i + "px");
                
            style = style +"."+nametool+"-item."+names[i]+" ."+nametool+"-icon {\n"+
            " margin: 0;\n"+
            " padding: 0 0px;\n"+
            " background-position-x: "+vsize+";\n"+
            " border-style: none;\n"+
            " border-color: transparent;}\n"+
            " \n";
        }


    
        mainlibutil.html.create_style(head, style);
    }
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
        alert(exception);
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

mainlibutil.designtime.CreateToolBarWindow = function (name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, names, funcs, destroyfunc){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp[name]){
        tmp[name]=mainlibutil.window.createhtml('_'+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, "../mainlib/css/maintoolstyle.css");
        tmp[name].onunload= destroyfunc ? destroyfunc : 
            function(){     
               try{
                  var tmpo=mainlibutil.global.getGlobal();
                  if (tmpo && tmpo[name])
                  tmpo[name]=undefined;}
               catch(error){}
            };
        if (names)    
           mainlibutil.designtime.CreateToolBarWindowTool(name, null, names, funcs);
        return tmp[name];
    } 
    
}

mainlibutil.designtime.CreateToolBarWindowTool = function (name, tools, names, funcs){
    var tmp=mainlibutil.global.getGlobal();
    if (name && names && funcs && tmp[name]){
        if (!tools) tools=name;
        if (!tmp[name].tools)
            tmp[name].tools={};
        tmp[name].tools[tools]=mainlibutil.html.create_tool(tmp[name].document, tools, names, funcs) ;
        //tmp[name+'_tools'] = tmp[name].tools;
    }    
}

mainlibutil.designtime.setWindowButtonState = function (name, tools, btnname , state){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp[name] && tmp[name].tools){
        if (!tools) tools=name;
        if (tmp[name].tools[tools]){
            var rowtool = tmp[name].tools[tools];
            if (rowtool[btnname]){
                var btn =  rowtool[btnname]; 
                if (btn.hasAttribute('off') && state!='off') 
                    btn.removeAttribute('off'); 
                if (btn.hasAttribute('on') && state!='on') 
                    btn.removeAttribute('on');
                if (btn.hasAttribute('disabled') && state!='disabled') 
                    btn.removeAttribute('disabled');    
                if (!btn.hasAttribute('off') && state=='off') 
                    btn.setAttribute('off', 'off'); 
                if (!btn.hasAttribute('on') && state=='on') 
                    btn.setAttribute('on', 'on');
                if (!btn.hasAttribute('disabled') && state=='disabled') 
                    btn.setAttribute('disabled', 'disabled');                              
            }       
        }    
    }
}

///

mainlibutil.designtime.getMainWindow = function (){
    mainlibutil.designtime.CreateToolBarWindow('maintool', 'Редактор' ,'5%','5%', '600','70','yes','yes',null,null,
                                           ['save','objinsp', 'forminsp', 'exit'],
                                           [function() {
                                                 mainlibutil.designtime.SaveAll();},
                                            function() {
                                                 mainlibutil.designtime.resetObjectInspector();
                                                       },
                                            function() {
                                                 mainlibutil.designtime.resetFormInspector();
                                                       },
                                            function() {
                                                 mainlibutil.designtime.destroyMainWindow();
                                                       }],
                                            mainlibutil.designtime.destroyMainWindow);
                                            mainlibutil.designtime.setMainWindowToolStatus();

}




mainlibutil.designtime.setMainWindowToolStatus = function (val){   
   if ((val==1 || !val)) 
       mainlibutil.designtime.setWindowButtonState('maintool', null, 'save', mainlibutil.designtime.isNeedSave() ?  'on' :  'disabled');
   if ((val==2 || !val)) 
       mainlibutil.designtime.setWindowButtonState('maintool', null, 'objinsp', mainlibutil.designtime.getObjectInspector() ?  'off' :  'on');
   if ((val==3 || !val)) 
       mainlibutil.designtime.setWindowButtonState('maintool', null, 'forminsp', mainlibutil.designtime.getFormInspector() ?  'off' :  'on');
}


mainlibutil.designtime.destroyMainWindow = function(){
    try{
    
        var tmp=mainlibutil.global.getGlobal();
        if (tmp && tmp['maintool'])
            tmp.maintool=undefined;
        if (!mainlibutil.designtime.isNeedSave())
            dvnci_exit();
        if (confirm("Выйти без сохранения?")){
            dvnci_exit();
            return;
        }
        setTimeout(function() {
            mainlibutil.designtime.getMainWindow();
        }, 100);
    }
    catch(error){
        dvnci_exit();
    }  
}

///  Object inspector

mainlibutil.designtime.getObjectInspector = function (force){
    var tmp=mainlibutil.global.getGlobal();
    if (!force && !tmp.objectinspectorwin) return null;
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

mainlibutil.designtime.resetObjectInspector = function(){
    var vis =  mainlibutil.designtime.getObjectInspector();
    var tmp=mainlibutil.global.getGlobal();
    if (vis && tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
    else
        mainlibutil.designtime.getObjectInspector(true);
    mainlibutil.designtime.setMainWindowToolStatus(2);
        
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
    mainlibutil.designtime.setMainWindowToolStatus(2);
    
}


// Form inspector


mainlibutil.designtime.getFormInspector = function (force){
    var tmp=mainlibutil.global.getGlobal();
    if (!tmp.forminspectorwin && !force) return null;
    if (tmp && !tmp.forminspectorwin){
 
        var forminspectorwin=mainlibutil.window.createhtml('_FormInspector','Окна','35%','35%', '600','200','yes','yes',null,null, "../mainlib/css/forminspector.css");
        tmp.forminspectorwin=forminspectorwin;
        tmp.forminspectordoc=forminspectorwin.document;
        forminspectorwin.onunload=mainlibutil.designtime.destroyFormInspector;
        var objdoc =forminspectorwin.document;
        try{
            var body=objdoc.getElementsByTagName('body')[0];
          

            var div = mainlibutil.html.create_div(body);
            div.setAttribute('id','toolbar');
            var btn1 = mainlibutil.html.create_button( div,null,'toolbar-item toggleable save','',function() {
                mainlibutil.document.writeDoc(mainlibutil.global.getStartupDoc());
            });
            mainlibutil.html.create_div(btn1,null,'toolbar-icon'); 
            var btn4 = mainlibutil.html.create_button( div,null,'toolbar-item toggleable exit','',function() {dvnci_exit();
            });
            mainlibutil.html.create_div(btn4,null,'toolbar-icon');          
          
          
            var div = mainlibutil.html.create_div(mainlibutil.html.create_div(body),null,"scrollWrapper");
            var table = mainlibutil.html.create_table(div,null,"scrollable");
            var tbody = mainlibutil.html.create_tbody(table);
            var tr = mainlibutil.html.create_tr(tbody);
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

mainlibutil.designtime.resetFormInspector = function(){
    var vis =  mainlibutil.designtime.getFormInspector();
    var tmp=mainlibutil.global.getGlobal();
    if (vis && tmp.forminspectorwin)
        tmp.forminspectorwin.close();
    else
        mainlibutil.designtime.getFormInspector(true);
    mainlibutil.designtime.setMainWindowToolStatus(3);
        
} 

mainlibutil.designtime.fillFormInspector = function (){
    
    var tbody = mainlibutil.designtime.getFormInspectorTbody();
    
    mainlibutil.dom.clearChildNode(tbody);   

    var tr = mainlibutil.html.create_tr(tbody);
    
    mainlibutil.html.create_tabel_header(tr,null,null,['Файл','id','caption','x','y','width','height','visible','alltop','resize','decorate','modal','O','X']);
   
    var fl= mainlibutil.global.getFormList();
 
                            
    for (var i=0; i<fl.length; ++i ){
        var formname=fl[i]['name'];
        formname=formname.toString();
        var tr= mainlibutil.html.create_tr(tbody);
       
        var td1= mainlibutil.html.create_td(tr);
        td1.innerHTML=fl[i]['file'] ? fl[i]['file'] : "";
        
        td1.className='static';
   
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'name');
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'caption');
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'left', '50px');       
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'top', '50px');
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'width', '50px');       
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'height', '50px'); 
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'visible', '50px'/*, ['','true','false']*/);
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'allwaystop', '50px'/*,, ['','true']*/);       
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'resizable', '50px'/*,, ['','true']*/);
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'decorated', '50px'/*,, ['','no']*/);
        mainlibutil.designtime.fiCreateRow(tr,fl[i],'modal', '50px'/*,, ['','true']*/);        
        
        var td11= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btno = mainlibutil.html.create_button( td11,'height: 15px;',null,'');
        btno.setAttribute('onclick','mainlibutil.designtime.openwindow("'+formname+ '");');
        
        var td12= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btnc = mainlibutil.html.create_button( td12,'height: 15px;',null,'');
        btnc.setAttribute('onclick','mainlibutil.designtime.closewindow("'+formname+ '");');
    
    }
}

mainlibutil.designtime.fiCreateRow = function(tr, tblrow, name, width, lst){
    var td= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0;' + width ? 'width: ' + width + ';' : '');
    var tmp= tblrow[name] ? tblrow[name] : '';
    if (lst)
        td.lst=lst; 
    td.innerHTML= tmp;
    td.elem=tblrow;
    td.value=tmp;
    td.propname=name;
    td.onclick=function(ev) {
        mainlibutil.designtime.fiPropertyRowFocus(ev);    
    }
}



mainlibutil.designtime.fiPropertyRowFocus = function(ev){
    try{
        var td = ev.target;
        mainlibutil.dom.clearChildNode(td);
        if (td.lst)
            var edit=mainlibutil.html.create_select(ev.target, 'text', td.value, td.lst);
        else
            var edit=mainlibutil.html.create_input(ev.target, 'text', td.value);
       
    
        edit.focus();
        edit.oldval=td.value;  
 
        edit.onblur= function(ev) {
            mainlibutil.designtime.fiPropertyLeaveFocus(ev);
        }

        edit.addEventListener( 'keyup' ,function (ev) {       
            if ((evn.keyIdentifier=="Enter"))
                mainlibutil.designtime.fiPropertyLeaveFocus(ev);
            else 
                ev.stopPropagation();
        });  
        ev.preventDefault();
        ev.stopPropagation();
    }
    catch(error){
        alert(error);
    }
}

mainlibutil.designtime.fiPropertyLeaveFocus = function(event){

    if (!event.target) return;
    var oldval=event.target.oldval;
    var value =event.target.value;
    var td=event.target.parentNode;
    td.removeChild(event.target);
    td.innerHTML=value;
    if ((oldval!=value) && (mainlibutil.designtime.fiCheckFormParam(td.propname,value))){  
        
        
        if (td.elem && td.elem['element']){     
            
            td.elem['element'].setAttribute(td.propname,value);
            td.elem[td.propname]=value;
            mainlibutil.designtime.closewindow(td.elem['name'], true);
            td.elem['param'] = mainlibutil.project.buildparam(td.elem['element']);
            mainlibutil.designtime.openwindow(td.elem['name']);

            
        }      
    }

          
    event.preventDefault();
    event.stopPropagation();   
}

 

mainlibutil.designtime.fiCheckFormParam = function(name, val){
    try{
        switch (name){
            case 'caption':{
                return true;
            }             
            case 'width':
            case 'height':        
            case 'top':
            case 'left':{
                var ind = val.search('/%/i');
                if (ind==-1){
                    var vl=parseInt(val);
                    if (vl!=vl) return undefined;
                }
                else{
                    var tmpval = val.substring(0,ind);
                    if ((vl!=vl) || (vl<0) || (vl>100)) return undefined;
                }
                return true;
            }
            case 'name':{
                return !mainlibutil.project.getFormInfo(val);
            }
            case 'visible':{
                return (val=='') || (val=='true') || (val=='false');
            } 
            case 'resizable':
            case 'resizable':
            case 'allwaystop':{
                return (val=='') || (val=='true');
            }
            case 'decorated':{
                return (val=='') || (val=='no');
            }  
        }
    }
    catch(error){ 
    }
    return false;
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
    mainlibutil.designtime.setMainWindowToolStatus(3);
    
}


mainlibutil.designtime.getLibInspector = function (force){
    try{
    mainlibutil.designtime.CreateToolBarWindow('libtool','Компоненты','65%','35%', '600','70','yes','yes',null,null);
    var libs =mainlibutil.global.getLibList();
    for (var i=0; i<libs.length;++i){
        var lib =libs[i];
        var btnsname =[];
        var btnsfunc =[];
        var comps =lib.components;
        
        for (var j=0; j<comps.length;++j){
            var name = lib.name;
            var hint = comps[j].hint;
            btnsname.push(comps[j].hint);
            btnsfunc.push(mainlibutil.designtime.setSelectedToolEvent);
        }
        
        mainlibutil.designtime.CreateToolBarWindowTool('libtool', lib.name , 
            btnsname, 
            btnsfunc); 
    }}
    catch(error){
        alert(error)
    }

}  

mainlibutil.designtime.setSelectedToolEvent = function(event){


if (event && event.target && event.target.parentNode){
    var trgt=event.target.parentNode;
    mainlibutil.designtime.setSelectedComponent(trgt.nametool, trgt.namebtn);
}
}

mainlibutil.designtime.setSelectedComponent = function(tool, comp){
    var tmp= mainlibutil.global.getGlobal(); 
    var set  = tool && comp;
    var result = null; 
    if (tmp){
        var select = tmp['selectedComponent'];  
        
        if (select && set && select.tool==tool && select.component==comp){
           tmp['selectedComponent'] =  null;
           mainlibutil.designtime.setWindowButtonState('libtool', tool , comp , 'on' );
           return null;}
       
        if (select){          
            result = {'tool' : select.tool , 'component' : select.component};
            if (!set) return result;
            mainlibutil.designtime.setWindowButtonState('libtool', result.tool , result.component , 'on' );
            }
        if (set){
            tmp['selectedComponent']={'tool' : tool , 'component' : comp};
            mainlibutil.designtime.setWindowButtonState('libtool', tool  , comp  , 'off' );}
    }
    return result;
}


mainlibutil.designtime.getSelectedComponent = function(){
var tmp = mainlibutil.designtime.setSelectedComponent();
if (tmp && tmp.tool && tmp.component){
    //alert(tmp.tool+' : '+ tmp.component);
    return mainlibutil.project.get_components(tmp.tool, tmp.component);
}
return null;
}


mainlibutil.designtime.destroyLibInspector = function(){
    
}




mainlibutil.designtime.SaveAll = function(){ 
    var fl= mainlibutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red){
            fl[i].red.save();
        }   
    }
    mainlibutil.designtime.setMainWindowToolStatus();
}

mainlibutil.designtime.isNeedSave = function (){
    var fl= mainlibutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red && fl[i].red.needsave)
            return true;        
    }   
    return false;
}

mainlibutil.designtime.openwindow = function(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (!fl[i].window){
                    fl[i]['needreload']=undefined;
                    var win=window.open(fl[i]['path'],fl[i]['name'],fl[i]['param'].toString());
                    win.document.domain=document.domain;
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


mainlibutil.designtime.closewindow = function (name, needreload){
    var fl =  mainlibutil.global.getFormList();
   
    if (fl){  
        for (var i=0; i<fl.length;++i){
            try{
                if (fl[i]['name']==name){
                    if (fl[i].window){
                        fl[i].window.onunload=null;
                        fl[i].window.close();
                    }
                    fl[i].window=null;
                    return;
                }
            }
            catch(error){
                alert(error);
            }
        }
    }
}

mainlibutil.designtime.createFormInProject =function(name, left, top, width, heigth, decorated){
    
    }

mainlibutil.designtime.removeFormFromProject =function(name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                
        }
        }
    }
}




  

    
