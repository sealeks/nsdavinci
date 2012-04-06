
var mainlibutil = {};

mainlibutil.util = {};

mainlibutil.startup = {};

mainlibutil.project = {};

mainlibutil.window = {};

mainlibutil.svg = {};

mainlibutil.html = {};

mainlibutil.dom = {};

mainlibutil.popup = {};

mainlibutil.www = {};

mainlibutil.xslttransform = {};

mainlibutil.document = {};

mainlibutil.designtime = {};

mainlibutil.global = {};

mainlibutil.error = {};

mainlibutil.regex = {};

mainlibutil.alarmtable = function(el){
    
    this.alarmelement=mainlibutil.document.findElementByTagName(el,'table');
    if (this.alarmelement){
        this.alarmelement.alarlistener=this;
        this.alarmelement.onalarm=function(ev){this.alarlistener.execute(ev);}}

}

function dvnci_open(name){
    if (dvnci_iseditable()) return;
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                if (!fl[i].window){
                    var win=window.open(fl[i]['path'],fl[i]['name'],fl[i]['param'].toString());
                   // win.document.domain=document.domain;
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


function dvnci_show_modal(name, url, param){
    if (dvnci_iseditable()) return null;
    return showModalDialog(name, url ? url : '' , param);
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

function set_win_redactor(win, redactor){   
    var fl =  mainlibutil.global.getFormList();   
    if (fl){  
        for (var i=0; i<fl.length;++i){        
            if (fl[i]['name']==win.name){
                fl[i].redactor_glb=redactor;
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

function dvnci_close_allwin(){
    try{
    var fl =  mainlibutil.global.getFormList();
    if (fl){      
        for (var i=0; i<fl.length;++i){
            if (fl[i].window!=window){
                fl[i].window.onunload=null;
                mainlibutil.dom.clearChildNode(fl[i].window.document.documentElement); 
                //fl[i].window=null;
            }
        }
    }
    }
    catch(err){
        alert(err);
    }
}

function exit(){
    if (dvnci_iseditable()) return;
    //dvnci_close_allwin()
    dvnci_exit();
    window.close();
}


function init_project_controller(){
    mainlibutil.global.getStartupDoc(document);   
    mainlibutil.project.init_form();
    if (dvnci_iseditable()) 
        mainlibutil.designtime.getMainWindow();
}

//



mainlibutil.util.remove_element_arr = function(arr,ind){
    for (var i=ind; i<arr.length-1;++i)
        arr[i]=arr[i+1];
    if (ind<arr.length) 
        arr.length=arr.length-1;
}


mainlibutil.util.trim = function(string)
{
return string.replace(/(^\s+)|(\s+$)/g, "");
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

mainlibutil.global.getGlobalPropertyEditor = function (){
    var tmp=mainlibutil.global.getGlobal();
    return tmp.globalpropertydialog;   
}

mainlibutil.global.setGlobalPropertyEditor = function (val){
    var tmp=mainlibutil.global.getGlobal();
    tmp.globalpropertydialog=val;   
}

//

mainlibutil.startup.init = function(){
    window.addEventListener('message', function () {
        window.close();
    }, false);
    if (dvnci_iseditable()){
        document.red = new redactor(document);
        mainlibutil.startup.initredactor(window.name, document.red);
        set_win_redactor(window, document.red);
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
            
            var tmp=mainlibutil.global.getGlobal();
            var elp=doc.getElementsByTagName('project')[0];
            var projectPath=elp.getAttribute('path');
            
            tmp.projectPath=projectPath;
            
            var els=doc.getElementsByTagName('form');
                                 
            var ellib=doc.getElementsByTagName('lib');
                                
            if (els)
                for (var i=0; i<els.length;++i)   
                    mainlibutil.project.addtoformlist(els[i]);
                          
            if (ellib)  {
                for (var i=0; i<ellib.length;++i)
                    mainlibutil.project.addtoliblist(ellib[i],i);}

        }
        catch(error){ 
            alert('Startup error: '+ error)
        }
    }
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

mainlibutil.project.addtoformlist = function(els){
    var tmp=mainlibutil.global.getGlobal();
    var prjpath=tmp.projectPath;
    var path = prjpath && els.getAttribute('file') ? prjpath.toString() + els.getAttribute('file').toString() : 
    els.getAttribute('file') ? els.getAttribute('file').toString() : null;
    if (path){            
        var param = mainlibutil.project.buildparam(els);
        var win=window.open(path, els.getAttribute('name')  ? els.getAttribute('name') :  '', param ? param : '');
        win.document.domain=document.domain; 
        var fl=mainlibutil.global.getFormList();
        fl.push({
            'name' : els.getAttribute('name'),
            'file' : els.hasAttribute('file') ? els.getAttribute('file') : '',
            'path'  : path,
            'param'  : param,
            'window'  : win,
            'top'  : els.hasAttribute('top') ? els.getAttribute('top') : null,
            'left'  : els.hasAttribute('left') ? els.getAttribute('left') : null,
            'width'  : els.hasAttribute('width') ? els.getAttribute('width') : null,
            'height'  : els.hasAttribute('height') ? els.getAttribute('height') : null,
            'caption'  : els.hasAttribute('caption') ? els.getAttribute('caption') : '',
            'decorated'  : els.hasAttribute('decorated') ? els.getAttribute('decorated') : true,
            'resizable'  : els.hasAttribute('resizable') ? els.getAttribute('resizable') : null,
            'modal'  : els.hasAttribute('modal') ? els.getAttribute('modal') : null,
            'allwaystop'  : els.hasAttribute('allwaystop') ? els.getAttribute('allwaystop') : null,
            'visible'  : ((els.hasAttribute('visible')) && (els.getAttribute('visible')=='false')) ? false : true,
            'element' : els
        });
    }   
}

mainlibutil.project.addtoliblist = function(els, i){   
    var ll=mainlibutil.global.getLibList();
    if (els.hasAttribute('xsd')){
        ll.push({
            'name' : els.hasAttribute('name') ? els.getAttribute('name') : ('unnamed'+i),
            'caption' : els.hasAttribute('caption') ? els.getAttribute('caption') : ('Library'+i),
            'path' : els.getAttribute('xsd'),
            'components' : mainlibutil.project.set_components(els.getAttribute('xsd'))
        })
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
                'hintup' : els[i].hasAttribute('hintup') ? els[i].getAttribute('hintup') : (els[i].hasAttribute('hint') ? els[i].getAttribute('hint') : null),
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

//

mainlibutil.popup.getbound = function(el, W, H, yd, dir){
    /*
       dir 0 -top, 1 -right, 2 - bottom(default) , 3 left
     */
    
     
    if ((dir==undefined) || (dir==null)) throw "Bound popup error";
  
    var x0 = parseFloat(el.getAttribute('x'));
    var y0 = parseFloat(el.getAttribute('y'));
    var h0 = parseFloat(el.getAttribute('height'));
    var w0 = parseFloat(el.getAttribute('width'));    
    
    
    var hh= h0 + 2*yd;
    var wh= w0 + 2*yd;
    
    var xc = (dir==2 || dir==0) ? (x0 + (w0-W) / 2) : ( dir==3 ? x0-yd- W : x0 - yd);
    var yc = (dir==2 || dir==0) ? ( dir==2 ? y0 - yd : y0 - yd - H ) : (y0 + (h0-H) / 2);
    
    
    var hc = (dir==2 || dir==0) ? H + hh : H;
    var wc = (dir==2 || dir==0) ? W : W + wh;
    return {'x': xc, 'y': yc, 'width': wc , 'height': hc} 
}


mainlibutil.popup.bpunds_intersect = function(popupbound, documenbound){
    var X0 =   popupbound.x < documenbound.x ? documenbound.x : popupbound.x;
    var Y0 =   popupbound.y < documenbound.y ? documenbound.y : popupbound.y;
    var X1 =   (popupbound.x + popupbound.width) < (documenbound.x + documenbound.width) ? 
        (popupbound.x + popupbound.width) : (documenbound.x + documenbound.width);
    var Y1 =   (popupbound.y + popupbound.height) < (documenbound.y + documenbound.height) ? 
        (popupbound.y + popupbound.height) : (documenbound.y + documenbound.height);;    
    
   return (X1-X0)*(Y1-Y0);
}


mainlibutil.popup.finddirect = function(el, W, H, yd){
    var windowbound = {
        'x': 0, 
        'y': 0, 
        'width': window.innerWidth , 
        'height': window.innerHeight
    };
    var popupbound0 =  mainlibutil.popup.getbound(el, W, H, yd,0);
    var popupbound1 =  mainlibutil.popup.getbound(el, W, H, yd,1);
    var popupbound2 =  mainlibutil.popup.getbound(el, W, H, yd,2);
    var popupbound3 =  mainlibutil.popup.getbound(el, W, H, yd,3);
    var range = [mainlibutil.popup.bpunds_intersect(popupbound2, windowbound),
    mainlibutil.popup.bpunds_intersect(popupbound1, windowbound),
    mainlibutil.popup.bpunds_intersect(popupbound3, windowbound),
    mainlibutil.popup.bpunds_intersect(popupbound0, windowbound)];
    var max = 0;          
    for (var i=1;i<range.length;i++){
        if (range[max] < range[i]) max=i; 
    } 
    switch(max) {
       case 1:return 1;
       case 2:return 3;
       case 3:return 0;     
    }
    return 2;
}

mainlibutil.popup.createsvgs = function(el, W, H, yd, dir, bodystyle, popupstyle){
    

    if ((dir==undefined) || (dir==null)) {
        dir = mainlibutil.popup.finddirect(el, W, H, yd);
    }
    
    var bounds=mainlibutil.popup.getbound(el, W, H, yd, dir);
    
    var h0 = parseFloat(el.getAttribute('height'));
    var w0 = parseFloat(el.getAttribute('width'));  
    
    var hh= h0 + 2*yd;
    var wh= w0 + 2*yd;
    
    var xc = bounds.x;
    var yc = bounds.y;
    var hc = bounds.height;
    var wc = bounds.width;
    
    var docelem = document.documentElement;
    
    var svg =mainlibutil.svg.create_svg(docelem, xc , yc ,  hc , wc);
    
    mainlibutil.svg.create_rect(svg, 0 , 0 ,  hc  , wc,  null , null , popupstyle ? popupstyle : 'fill: white; opacity: 0.0;', null);
    
    svg.popupbody = mainlibutil.svg.create_svg(svg, dir==1 ? wh : 0 , dir==2 ? hh : 0 ,  H , W);
    
    mainlibutil.svg.create_rect(svg.popupbody, 0 , 0 ,  H  , W,  null , null , bodystyle ?  bodystyle : 'fill: white; opacity: 1.0;', null);
    
    return svg;
}

// xslttransform


mainlibutil.xslttransform.rootDocument = function (){ 
    if (window.__rootDocument)
        return window.__rootDocument;
    window.__rootDocument = mainlibutil.document.readDoc(window.document.URL);
    return window.__rootDocument;
}


mainlibutil.xslttransform.literootDocument = function (){ 
    if (window.__literootDocument){
        mainlibutil.dom.clearChildNode(window.__literootDocument.documentElement);
        return window.__literootDocument;}
    window.__literootDocument = mainlibutil.document.readDoc(window.document.URL);
    mainlibutil.dom.clearChildNode(window.__literootDocument.documentElement);
    return window.__literootDocument;
}

//mainlibutil.xslttransform.literootDocumentElement = function (){     
//    return mainlibutil.xslttransform.literootDocument().documentElement;
//}


mainlibutil.xslttransform.xsltDocument = function(){
    if (window.__xsltDocument)
        return window.__xsltDocument;    
    var root = mainlibutil.xslttransform.rootDocument();
    if ((root) && (root.childNodes.length>1)){
        if (root.childNodes[0].target=='xml-stylesheet'){
            if (root.childNodes[0].data){
                var urlxslt=root.childNodes[0].data.toString();
                var finded=urlxslt.search('type="text/xsl"');
                if (finded==-1)
                    finded=urlxslt.search("href='");
                if (finded!=-1){
                    urlxslt=urlxslt.substring(6,urlxslt.length);
                    finded=urlxslt.search('"') ;
                    if (finded!=-1){
                        urlxslt=urlxslt.substring(0,finded);
                        window.__xsltDocument = mainlibutil.document.readDoc(urlxslt);
                    }
                }
            } 
        }
    }
    return window.__xsltDocument;
}

mainlibutil.xslttransform.xsltProcessor = function(){
    if (window.__xsltProcessor) return window.__xsltProcessor;
    window.__xsltProcessor=new XSLTProcessor();
    var xsltdoc = mainlibutil.xslttransform.xsltDocument();
    if (window.__xsltProcessor &&  xsltdoc)
        window.__xsltProcessor.importStylesheet(xsltdoc);
    else
        throw 'XSLT transform error';       
    return window.__xsltProcessor;
}


mainlibutil.xslttransform.tranformDocument = function(doc){
    return mainlibutil.xslttransform.xsltProcessor().transformToDocument(doc);
}

mainlibutil.xslttransform.tranform_and_getById = function(doc, id){
    var transdoc = mainlibutil.xslttransform.xsltProcessor().transformToDocument(doc);
    return transdoc.getElementById(id);
}


//  window

mainlibutil.window.create = function(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate){
    var tmp='caption=' + ( caption ? caption :  "") +
    ',left='+ (left ? left : '0') +
    ',top=' + (top ? top : '0') +
    ',width=' + (width ? width : '200px') +
    ',height=' + (height ? height : '200px') +
    ',tooltip=' + (tooltip ? 'yes' : '0') +
    ',resizable='+ (false ? 'yes' : 'no') +
    ',allwaystop='+ (allwaystop ? 'yes' : '0') +
    (nodecorate ? ',decorated=no' : '') +
    ';'
    return window.open('', name , tmp);
}


mainlibutil.window.create_modal = function(url,  caption, value ,top, left, width, height, tooltip, allwaystop, nodecorate){
    var tmp='caption=' + ( caption ? caption :  "") +
    ',left='+ (left ? left : '0') +
    ',top=' + (top ? top : '0') +
    ',width=' + (width ? width : '200px') +
    ',height=' + (height ? height : '200px') +
    ',tooltip=' + (tooltip ? 'yes' : '0') +
    ',resizable='+ (false ? 'yes' : 'no') +
    ',allwaystop='+ (allwaystop ? 'yes' : '0') +
    (nodecorate ? ',decorated=no' : '') +
    ';'
    mainlibutil.global.setGlobalPropertyEditor({'value': value});
    window.showModalDialog(url, null , tmp);
    
    var ret = mainlibutil.global.getGlobalPropertyEditor();
    if (!ret || ret==value) return null;
    mainlibutil.global.setGlobalPropertyEditor();
    return ret;
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

mainlibutil.regex.check = function (value, expr){
    var re= new RegExp(expr);
    return re.test(value);
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

mainlibutil.html.create_link = function (parent, rel, type, href){
    var newel = mainlibutil.html.create('link', parent);
    if (!newel) return;
    newel.setAttribute('rel', rel ? rel : 'stylesheet');
    newel.setAttribute('type', type ? type : 'text/css');
    if (href) newel.setAttribute('href', href);
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
    newop.setAttribute('selected','');
    newop.innerHTML=value;

    for(var i=0; i < list.length; i++){
        if (list[i]!=value){
            var newop = mainlibutil.html.create('option', newel);
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

mainlibutil.html.create_tool = function (doc, nametool, names, hints, funcs, size, header, headerstyle){
    if (names){
        var body=doc.getElementsByTagName('body')[0];
        var result = {};
        if (body) {
            if (header){
                var divhead = mainlibutil.html.create_div(body, headerstyle); 
                divhead.innerHTML=header;
            }
            mainlibutil.html.create_tool_style(doc, nametool, names,  size);
            var div = mainlibutil.html.create_div(body);
            div.setAttribute('class','toolbar');
            for (var i=0;i<names.length;++i){
                var btn = mainlibutil.html.create_button( div,null,nametool+'-item toggleable '+names[i],'', (funcs && funcs.length > i) ? funcs[i] : null);               
                btn.namebtn=names[i];
                btn.nametool=nametool;
                if ( hints &&  hints.length>i)
                    btn.setAttribute('title', hints[i])
                var dv = mainlibutil.html.create_div(btn,null,nametool+'-icon');
                if (hints &&  hints.length>i)
                    dv.setAttribute('title', hints[i]);
                result[names[i]] = btn;
            } 
            return result;
        }
    }
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
        " padding: 0 0px;\n"+
        " background-color: transparent;\n"+
        " border-style: none;\n"+
        " border-color: transparent;}\n"+
        " \n"+


        "."+nametool+"-item.toggleable {\n"+
        " padding-top: 0px;}\n"+
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

mainlibutil.dom.check_is_parent  = function(canparent,test,self){
     if (!test) return false;
     if (test==canparent) return (self) ? true : false;
     return mainlibutil.dom.check_is_parent (canparent,test.parentNode,true);
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

mainlibutil.svg.create_g = function (parent){
    
    var newel = mainlibutil.svg.create('g', parent);
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
    
    var body = mainlibutil.html.create_body(newel, 'margin: 0px;  height: '+height+'px; ');
    
    var div = mainlibutil.html.create_div(body, style + ' overflow: hidden;');
    
    var span = mainlibutil.html.create_span(div, 'line-height: '+ height/2 + 'px;');
    
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
        x ,y, height, width);
   
   

    var headertext=mainlibutil.svg.foriegn_text(headersvg, 0 , 0  , height, width ,text,
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


//


mainlibutil.www.create_window = function(doc, id, x, y, width, height, style){
    
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

mainlibutil.www.correct_window_height = function (win, innerheight){
    if (win.innerHeight!=innerheight){
        var correctH =  win.outerHeight + (innerheight - win.innerHeight);
        win.resizeTo(win.outerWidth,correctH);
    }
}

mainlibutil.www.create_tbwindow = function (name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, names, hints,  funcs, destroyfunc){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp[name]){
        tmp[name]=mainlibutil.window.createhtml('_'+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, "../mainlib/css/maintoolstyle.css");
        tmp[name].onunload= destroyfunc ? destroyfunc : 
        function(){     
            try{
                var tmpo=mainlibutil.global.getGlobal();
                if (tmpo && tmpo[name])
                    tmpo[name]=undefined;
            }
            catch(error){}
        };
        if (names)    
            mainlibutil.www.create_tbwindow_tools(name, null, names, hints, funcs);
        return tmp[name];
    }   
}

mainlibutil.www.create_modalwindow = function (name, caption, top, left, width, height, tooltip, allwaystop, nodecorate){
    var result=mainlibutil.window.mainlibutil.window.create_modal(+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate);
    return result;
}

mainlibutil.www.create_tbwindow_tools = function (name, tools, names, hints, funcs, size, header, headerstyle){
    var tmp=mainlibutil.global.getGlobal();
    if (name && names && funcs && tmp[name]){
        if (!tools) tools=name;
        if (!tmp[name].tools)
            tmp[name].tools={};
        tmp[name].tools[tools]=mainlibutil.html.create_tool(tmp[name].document, tools, names, hints, funcs, size, header, headerstyle) ;
        tmp[name+'_tools']=tmp[name].tools[tools];
    }    
}

mainlibutil.www.set_tbwindow_btnstatus = function (name, tools, btnname , state){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp[name+'_tools']){
        if (!tools) tools=name;
        if (tmp[name+'_tools']){
            var rowtool = tmp[name+'_tools'];
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


//



mainlibutil.alarmtable.prototype.execute = function(evnt) {
    this.cleartable();   
    this.fillrowtab(evnt);
}

mainlibutil.alarmtable.prototype.cleartable = function() {
    var el = this.alarmelement;
    if (el==null) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    while (el.children.length>1)
        el.removeChild(el.lastChild);
}
        
          

  
mainlibutil.alarmtable.prototype.fillrowtab = function(evnt){
    var el = this.alarmelement;
    if ((el==null) || (evnt==null)) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    for (var i=0;i<evnt.length;++i){
        this.insertrow(el, evnt[i]);
    }
     
}


mainlibutil.alarmtable.prototype.insertrow = function(el, arr) {

    if (el.children.length==0) return;
    var tr  = document.createElementNS('http://www.w3.org/1999/xhtml','tr');
    if (arr[2]==0){
        tr.setAttribute("class", (arr[1]>2) ? "avaron" : ((arr[1]>1) ? "alarmon" : "noticeon"));
    }
    else{
        tr.setAttribute("class", (arr[1]>2) ? "avarkvit" : ((arr[1]>1) ? "alarmkvit" : "noticekvit"));
    }

      
    for (var i=0; i<arr.length-1 ;++i){
        if ((i==0) || (i>2)){
            var td = document.createElement('td');
            if (i==0){
                var tm= new Date(0,0,0, arr[i].getHours() ,arr[i].getMinutes() 
                    +arr[i].getTimezoneOffset(),arr[i].getSeconds());
                var ta = document.createTextNode(tm.toLocaleTimeString());
                var sp = document.createElementNS('http://www.w3.org/1999/xhtml','span');
                sp.setAttribute("class", "smallfont");
                sp.appendChild(ta);
                td.appendChild(sp);
                tr.appendChild(td);
            }
            else{
                var ta = document.createTextNode(arr[i]);
                var sp = document.createElement('span');
                sp.setAttribute("class", "smallfont");
                sp.appendChild(ta);
                td.appendChild(sp);
                tr.appendChild(td);
            }
        }
    }
      
el.appendChild(tr);
}

//


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

mainlibutil.document.findElementById = function (el, id){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.getAttribute('id')==id) return e;
        var result = mainlibutil.document.findElementById(e, id);
        if (result) 
            return result;      
    }
}

mainlibutil.document.findElementByTagName = function (el, name){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.localName==name) return e;
        var result = mainlibutil.document.findElementByTagName(e, name);
        if (result) 
            return result;      
    }
}

// radactor util


///




mainlibutil.designtime.getMainWindow = function (){
    mainlibutil.www.create_tbwindow('maintool', 'Редактор' ,'100' , '100', '600','64','yes','yes',null,null,
        ['save','objinsp', 'forminsp','libinsp', 'exit'],
        ['Сохранить','Редактор свойств', 'Редактор форм','Панель компонентов', 'Выход'],
        [function() {
            mainlibutil.designtime.SaveAll();
        },
        function() {
            mainlibutil.designtime.resetObjectInspector();
        },
        function() {
            mainlibutil.designtime.resetFormInspector();
        },
        function() {
            mainlibutil.designtime.resetLibInspector();
        },           
        function() {
            mainlibutil.designtime.destroyMainWindow();
        }],
        mainlibutil.designtime.destroyMainWindow);
        
        
    var tmp=mainlibutil.global.getGlobal();
    
        
    tmp.maintool.onload =  function() {
            //setTimeout( function() {
            //mainlibutil.www.correct_window_height(tmp.maintool,30);}, 1000);
        }  
    
    
     
    mainlibutil.designtime.setMainWindowToolStatus();
    tmp.maintool.focus();
    
}




mainlibutil.designtime.setMainWindowToolStatus = function (val){ 
    if ((val==1 || !val)) 
        mainlibutil.www.set_tbwindow_btnstatus('maintool', null, 'save', mainlibutil.designtime.isNeedSave() ?  'on' :  'disabled');
    if ((val==2 || !val)) 
        mainlibutil.www.set_tbwindow_btnstatus('maintool', null, 'objinsp', mainlibutil.designtime.getObjectInspector() ?  'off' :  'on');
    if ((val==3 || !val)) 
        mainlibutil.www.set_tbwindow_btnstatus('maintool', null, 'forminsp', mainlibutil.designtime.getFormInspector() ?  'off' :  'on');
    if ((val==4 || !val)) 
        mainlibutil.www.set_tbwindow_btnstatus('maintool', null, 'libinsp', mainlibutil.designtime.getLibInspector() ?  'off' :  'on');
}


mainlibutil.designtime.destroyMainWindow = function(){
        var tmp=mainlibutil.global.getGlobal();
        if (tmp && tmp.maintool)
            tmp.maintool=undefined;
        if (!mainlibutil.designtime.isNeedSave()){          
            dvnci_exit();
            return;}
        if (confirm("Выйти без сохранения?")){
            dvnci_exit();
            return;
        } 
        else{
        setTimeout(function() {
            mainlibutil.designtime.getMainWindow();
        }, 10);}
}


///  Object inspector

mainlibutil.designtime.getObjectInspector = function (force){
    var tmp=mainlibutil.global.getGlobal();
    if (!force && !tmp.objectinspectorwin) return null;
    if (tmp && !tmp.objectinspectorwin){
        var objectinspectorwin=mainlibutil.window.createhtml('_ObjectInspector','Свойства','100', '900', '400','650','yes','yes',null,null, "../mainlib/css/objectinspector.css");
        tmp.objectinspectorwin=objectinspectorwin;
        tmp.objectinspectordoc=objectinspectorwin.document;
        objectinspectorwin.onunload=mainlibutil.designtime.destroyObjectInspector;
        var objdoc =objectinspectorwin.document;
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
        var current=mainlibutil.designtime.getCurrentRedactor();
        if (current)
            current.show_property();
              
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
    if (!tmp.formtool && !force) return null;
    if (tmp && !tmp.formtool){

        mainlibutil.www.create_tbwindow('formtool', 'Окна' ,'600','100', '600','200','yes','yes',null,null,
            ['add', 'new'],
            ['Добавить из файла','Новая форма'],
            [
            function() {
                mainlibutil.designtime.addwindowfromfile();             
            },
            function() {
                mainlibutil.designtime.addnewwindow();
            }]);
    
        var objdoc =tmp.formtool.document;
        tmp.formtool.onunload=mainlibutil.designtime.destroyFormInspector;

        var body=objdoc.getElementsByTagName('body')[0];
        var head=objdoc.getElementsByTagName('head')[0];
        mainlibutil.html.create_link(head, 'stylesheet', 'text/css',"../mainlib/css/forminspector.css");
        var div = mainlibutil.html.create_div(mainlibutil.html.create_div(body),null,"scrollWrapper");
        var table = mainlibutil.html.create_table(div,null,"scrollable");
        var tbody = mainlibutil.html.create_tbody(table);
        mainlibutil.html.create_tr(tbody);
        tmp.formtooltbody=tbody;
    }
 
    mainlibutil.designtime.fillFormInspector();
    return (tmp && tmp.formtool) ? tmp.formtool : null;
}

mainlibutil.designtime.resetFormInspector = function(){
    var vis =  mainlibutil.designtime.getFormInspector();
    var tmp=mainlibutil.global.getGlobal();
    if (vis && tmp.formtool)
        tmp.formtool.close();
    else
        mainlibutil.designtime.getFormInspector(true);
    var tmp=mainlibutil.global.getGlobal();
    tmp.formtool.focus();
    mainlibutil.designtime.setMainWindowToolStatus(3);
        
} 

mainlibutil.designtime.fillFormInspector = function (){
    var tmp=mainlibutil.global.getGlobal();
    var tbody = tmp.formtooltbody;
    
    mainlibutil.dom.clearChildNode(tbody);   

    var tr = mainlibutil.html.create_tr(tbody);
    
    mainlibutil.html.create_tabel_header(tr,null,null,
                                         ['Файл','id','caption','x','y','width','height','visible','alltop','resize','decorate','modal','0/X','-']);
   
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
        btno.setAttribute('onclick','mainlibutil.designtime.resetwindow("'+formname+ '");');
 
        
        var td13= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btnd = mainlibutil.html.create_button( td13,'height: 15px;',null,'');
        btnd.setAttribute('onclick','mainlibutil.designtime.removeFormFromProject("'+formname+ '");');
    
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
            if ((ev.keyIdentifier=="Enter"))
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
        var fdoc = mainlibutil.global.getStartupDoc();
        fdoc.needsave=true;
        mainlibutil.designtime.setMainWindowToolStatus();

    }

          
    event.preventDefault();
    event.stopPropagation();   
}

 

mainlibutil.designtime.fiCheckFormParam = function(name, val){
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
    return false;
}



mainlibutil.designtime.destroyFormInspector = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.formtool)
        tmp.formtool=undefined;
    if (tmp && tmp.formtooltbody)
        tmp.formtooltbody=undefined; 
    mainlibutil.designtime.setMainWindowToolStatus(3);  
}

//


mainlibutil.designtime.getLibInspector = function (force){    
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && !tmp.libtool && !force) return null;
    if (!tmp.libtool){
        var libs =mainlibutil.global.getLibList();
        
        var heigth = libs.length>0 ? 86 + 52 * (libs.length-1) : 46;
        
        mainlibutil.www.create_tbwindow('libtool','Библиотека','300','100', '600',heigth,'yes','yes',null,null);
        tmp.libtool.onunload=mainlibutil.designtime.destroyLibInspector;
    
        var libs =mainlibutil.global.getLibList();
        for (var i=0; i<libs.length;++i){
            var lib =libs[i];
            var btnsname =[];
            var btnsfunc =[];
            var btnshint =[];
            var comps =lib.components;        
            for (var j=0; j<comps.length;++j){
                btnsname.push(comps[j].hint);
                btnsfunc.push(mainlibutil.designtime.setSelectedToolEvent);
                btnshint.push(comps[j].hintup);
            }        
            mainlibutil.www.create_tbwindow_tools('libtool', lib.name , 
                btnsname, 
                btnshint, 
                btnsfunc, 
                null, 
                lib.caption, 
                "background-color: #E7E7E7; margin: 0px; border-width: 1px 0px ; border-color: yellow; border-style: solid; text-align: center; color: #040347)"); 
        }
        
        tmp.libtool.onload= function() {alert('test');}

    }
    return (tmp && tmp.libtool) ? tmp.libtool : null;

}  



mainlibutil.designtime.resetLibInspector = function(){
    
    var tmp=mainlibutil.global.getGlobal();
    if (tmp.libtool)
        tmp.libtool.close();
    else
        mainlibutil.designtime.getLibInspector(true);
    var tmp=mainlibutil.global.getGlobal();
    tmp.libtool.focus();
    mainlibutil.designtime.setMainWindowToolStatus(4);     
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
            mainlibutil.www.set_tbwindow_btnstatus('libtool', tool , comp , 'on' );
            return null;
        }
       
        if (select){          
            result = {
                'tool' : select.tool , 
                'component' : select.component
            };
            if (!set) return result;
            mainlibutil.www.set_tbwindow_btnstatus('libtool', result.tool , result.component , 'on' );
        }
        if (set){
            tmp['selectedComponent']={
                'tool' : tool , 
                'component' : comp
            };
            mainlibutil.www.set_tbwindow_btnstatus('libtool', tool  , comp  , 'off' );
        }
    }
    return result;
}


mainlibutil.designtime.getSelectedComponent = function(){
    var tmp = mainlibutil.designtime.setSelectedComponent();
    return (tmp && tmp.tool && tmp.component)? mainlibutil.project.get_components(tmp.tool, tmp.component): null;
}


mainlibutil.designtime.destroyLibInspector = function(){
    var tmp=mainlibutil.global.getGlobal();
    if (tmp && tmp.libtool)
        tmp.libtool=undefined;
    mainlibutil.designtime.setMainWindowToolStatus(4);  
}



//

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


mainlibutil.designtime.closewindow = function (name){
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

mainlibutil.designtime.resetwindow = function (name){
    var fl =  mainlibutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i){
            try{
                if (fl[i]['name']==name){
                    if (fl[i].window)
                        mainlibutil.designtime.closewindow(name);
                    else
                        mainlibutil.designtime.openwindow(name);              
                }
            }
            catch(error){
                alert(error);
            }
        }
    }
}

mainlibutil.designtime.windowstatus = function (name){
    var fl =  mainlibutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i)
            if (fl[i]['name']==name)
                return fl[i].window ? true : false;
        }
    return false;
}

mainlibutil.designtime.SaveAll = function(){ 
    var fl= mainlibutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red){
            fl[i].red.save();
        }   
    }
    var fdoc = mainlibutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) {
        mainlibutil.document.writeDoc(fdoc);
        fdoc = mainlibutil.global.getStartupDoc();
        fdoc.needsave=undefined;
    }    
    mainlibutil.designtime.setMainWindowToolStatus();
}

mainlibutil.designtime.isNeedSave = function (){
    var fl= mainlibutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red && fl[i].red.needsave)
            return true;        
    }   
    var fdoc = mainlibutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) return true;
    return false;
}

mainlibutil.designtime.setCurrentRedactor = function (win){
    var tmp= mainlibutil.global.getGlobal();
    if (!win){
        tmp.currentred = null;
        return;
    }
    var fl =  mainlibutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['window']==win){
                tmp.currentred=fl[i]['redactor_glb'];  
            }
        }
    }
}

mainlibutil.designtime.getCurrentRedactor = function (){
    var tmp= mainlibutil.global.getGlobal();
    return tmp.currentred;
}

mainlibutil.designtime.findwindow = function (name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                return fl[i].window;
            }
        }
    }
    return null;   
}

mainlibutil.designtime.windowexists = function (name){
    var fl =  mainlibutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                return true;
            }
        }
    }
    return false;   
}



mainlibutil.designtime.addwindowfromfile = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return; 
    var openddoc = mainlibutil.document.readDoc(openfile);
    if (!openddoc){
        alert('Документ '+openfile+' не был открыт!');
        return;
    }
    var openform= prompt('Введите имя формы','');
    if (!openform || openform=='') return; 
    if (!mainlibutil.regex.check(openform,'[A-Za-z][A-Za-z0-9]*')){
        alert('Имя формы '+openform+' некорректно!');
        return;
    }
    if (mainlibutil.designtime.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    mainlibutil.designtime.addform(openfile,openform); 
}
               
mainlibutil.designtime.addnewwindow = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return;          
    if (!mainlibutil.regex.check(openfile,'[A-Za-z][A-Za-z0-9]*\\.(xml|html|htm)')){
        alert('Имя формы '+openfile+' некорректно!');
        return;
    }
               
    var openddoc = mainlibutil.document.readDoc(openfile);
    if (openddoc){
        alert('Документ '+openfile+' уже существует!!');
        return;
    }
               
    var openform= prompt('Введите имя формы','');
    if (!openform || openform=='') return;
    if (!mainlibutil.regex.check(openform,'[A-Za-z][A-Za-z0-9]*')){
        alert('Имя формы '+openform+' некорректно!');
        return;
    }
    if (mainlibutil.designtime.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    mainlibutil.designtime.createfileform(openfile);
    mainlibutil.designtime.addform(openfile,openform);
           
}

mainlibutil.designtime.addform = function(file, name){
    try{       
        var doc = mainlibutil.global.getStartupDoc();
        var elp=doc.getElementsByTagName('project')[0];           
        var els=doc.getElementsByTagName('form');
        var el=els.length>0 ? els[els.length-1] : null;
        var newel=elp.ownerDocument.createElement('form');
        newel.setAttribute('name',name);
        newel.setAttribute('file',file);
        newel.setAttribute('left','10%');
        newel.setAttribute('top','10%');
        newel.setAttribute('width','50%');
        newel.setAttribute('height','50%');
        newel.setAttribute('caption',name);
        newel.setAttribute('decorated','no');
        elp.insertBefore(newel,el ? el.nextSibling : null);
        mainlibutil.project.addtoformlist(newel);
        mainlibutil.designtime.fillFormInspector();
        var fdoc = mainlibutil.global.getStartupDoc();
        if (fdoc && !fdoc.needsave) fdoc.needsave=true;
        mainlibutil.designtime.setMainWindowToolStatus();
    }
    catch(error){
        alert(error);
    }
       
}

mainlibutil.designtime.createfileform = function(file){
    var tmp=mainlibutil.global.getGlobal();
    var prjpath=tmp.projectPath;
    var txt = '<?xml-stylesheet href="../mainlib/lib.xsl" type="text/xsl"?>\n'+
    '<svg xmlns="http://www.w3.org/2000/svg" xmlns:mlib="http://dvnci/mlib" xmlns:xlink="http://www.w3.org/1999/xlink" width="100%" height="100%" version="1.1" style="" onload="mainlibutil.startup.init()">\n'+
    '\n'+
    '</svg>\n';
    return dvnci_writefile(prjpath.toString()+file,txt);      
}


mainlibutil.designtime.removeFormFromProject =function(name){
    if (confirm('Удалить форму "'+name+'" из проекта?')){
        try{
            var fl =  mainlibutil.global.getFormList();
            if (fl){  
                for (var i=0; i<fl.length;++i){
                    if (fl[i]['name']==name){
                        mainlibutil.designtime.closewindow(name);
                        mainlibutil.util.remove_element_arr(fl,i);               
                        var fdoc = mainlibutil.global.getStartupDoc();
                        var projel=fdoc.getElementsByTagName('project')[0];
                        var els=fdoc.getElementsByTagName('form');
                
                        for (var j=0; j<els.length;++j){
                            if (els[j].getAttribute('name')==name){
                                els[j].parentNode.removeChild(els[j]);
                                mainlibutil.designtime.fillFormInspector();
                                if (fdoc && !fdoc.needsave) fdoc.needsave=true;
                                mainlibutil.designtime.setMainWindowToolStatus();
                                return;
                            }
                        }
                    }
                }
            }
        }
    catch(error){
        alert(error);
    }
}
}

mainlibutil.designtime.propertydialog = function(name, value){
    return mainlibutil.window.create_modal('../mainlib/html/propertydialog.html',name , value, '20%', '20%', '60%', '60%', '1', 'yes');       
}




  

    
