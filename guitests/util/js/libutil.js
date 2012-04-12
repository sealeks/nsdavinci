
var libutil = {};

libutil.util = {};

libutil.startup = {};

libutil.project = {};

libutil.window = {};

libutil.svg = {};

libutil.html = {};

libutil.dom = {};

libutil.popup = {};

libutil.www = {};

libutil.xslttransform = {};

libutil.document = {};

libutil.global = {};

libutil.error = {};

libutil.regex = {};

libutil.alarmtable = function(el){
    
    this.alarmelement=libutil.document.findElementByTagName(el,'table');
    if (this.alarmelement){
        this.alarmelement.alarlistener=this;
        this.alarmelement.onalarm=function(ev){this.alarlistener.execute(ev);}}

}

function dvnci_open(name){
    if (dvnci_iseditable()) return;
    var fl =  libutil.global.getFormList();
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
    var fl =  libutil.global.getFormList();
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

function set_win_designer(win, designer){   
    var fl =  libutil.global.getFormList();   
    if (fl){  
        for (var i=0; i<fl.length;++i){        
            if (fl[i]['name']==win.name){
                fl[i].designer_glb=designer;
                return;
            }
        }
    }
}



function dvnci_close_win(){
    var fl =  libutil.global.getFormList();
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
    var fl =  libutil.global.getFormList();
    if (fl){      
        for (var i=0; i<fl.length;++i){
            if (fl[i].window!=window){
                fl[i].window.onunload=null;
                libutil.dom.clearChildNode(fl[i].window.document.documentElement); 
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
    libutil.global.getStartupDoc(document);   
    libutil.project.init_form();
    if (dvnci_iseditable() && designutil.toolwin) 
        designutil.toolwin.getMainWindow();
}

//



libutil.util.remove_element_arr = function(arr,ind){
    for (var i=ind; i<arr.length-1;++i)
        arr[i]=arr[i+1];
    if (ind<arr.length) 
        arr.length=arr.length-1;
}


libutil.util.trim = function(string)
{
return string.replace(/(^\s+)|(\s+$)/g, "");
}




//

libutil.global.getGlobal = function (){
    return window.dvnci_globalobject();
}

libutil.global.getFormList = function (){
    var tmp=libutil.global.getGlobal();
    if (tmp && !tmp.formlist)
        tmp.formlist=[];
    return (tmp && tmp.formlist) ? tmp.formlist : null;
}

libutil.global.getLibList = function (){
    var tmp=libutil.global.getGlobal();
    if (tmp && !tmp.liblist)
        tmp.liblist=[];
    return (tmp && tmp.liblist) ? tmp.liblist : null;
}

libutil.global.getStartupDoc = function (doc){
    var tmp=libutil.global.getGlobal();
    if (tmp && !tmp.startupdocument && doc)
        tmp.startupdocument=doc;
    return (tmp && tmp.startupdocument) ? tmp.startupdocument : null;
}

libutil.global.getGlobalPropertyEditor = function (){
    var tmp=libutil.global.getGlobal();
    return tmp.globalpropertydialog;   
}

libutil.global.setGlobalPropertyEditor = function (val){
    var tmp=libutil.global.getGlobal();
    tmp.globalpropertydialog=val;   
}

//

libutil.startup.init = function(){
    window.addEventListener('message', function () {
        window.close();
    }, false);
    if (dvnci_iseditable()){
        document.red = new designer(document);
        libutil.project.add_design_style(document);
        libutil.startup.initdesigner(window.name, document.red);
        set_win_designer(window, document.red);
    }
    window.onunload=dvnci_close_win;

}

libutil.startup.initdesigner = function(name, red){
    var fl =  libutil.global.getFormList();
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

libutil.project.init_form = function(){
    var doc = libutil.global.getStartupDoc();
    if (doc){
        try{
            
            var tmp=libutil.global.getGlobal();
            var elp=doc.getElementsByTagName('project')[0];
            var projectPath=elp.getAttribute('path');
            
            tmp.projectPath=projectPath;
            
            var els=doc.getElementsByTagName('form');
                                 
            var ellib=doc.getElementsByTagName('lib');
                                
            if (els)
                for (var i=0; i<els.length;++i)   
                    libutil.project.addtoformlist(els[i]);
                          
            if (ellib)  {
     
                for (var i=0; i<ellib.length;++i)
                    libutil.project.addtoliblist(ellib[i],i);}

        }
        catch(error){ 
            alert('Startup error: '+ error)
        }
    }
}


libutil.project.buildparam = function(el){
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

libutil.project.addtoformlist = function(els){
    var tmp=libutil.global.getGlobal();
    var prjpath=tmp.projectPath;
    var path = prjpath && els.getAttribute('file') ? prjpath.toString() + els.getAttribute('file').toString() : 
    els.getAttribute('file') ? els.getAttribute('file').toString() : null;
    if (path){            
        var param = libutil.project.buildparam(els);
        var win=window.open(path, els.getAttribute('name')  ? els.getAttribute('name') :  '', param ? param : '');       
        win.document.domain=document.domain; 
        var fl=libutil.global.getFormList();
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


libutil.project.add_design_style  = function(doc){
     if (doc.documentElement){
         var dstyle = ".designer_selected { opacity: 0.8; outline: 1px solid red;} \n"+
             "*[isgoupelement]{ outline: 1px dashed green; } \n"+
             "*[isgoupelement].designer_selected { opacity: 0.8; outline: 1px solid red;}";
         }
      libutil.html.create_style(doc.documentElement, dstyle);              
}

libutil.project.addtoliblist = function(els, i){   
    var ll=libutil.global.getLibList();
    if (els.hasAttribute('xsd')){
        ll.push({
            'name' : els.hasAttribute('name') ? els.getAttribute('name') : ('unnamed'+i),
            'caption' : els.hasAttribute('caption') ? els.getAttribute('caption') : ('Library'+i),
            'path' : els.getAttribute('xsd'),
            'components' : libutil.project.set_components(els.getAttribute('xsd'))
        })
    } 
}

libutil.project.set_components = function(path){
    var result = [];
    var doc = libutil.document.readDoc(path);
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

libutil.project.get_components = function(tool, name){
    var ll=libutil.global.getLibList();
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



libutil.project.getFormInfo = function(name){
    var fl =  libutil.global.getFormList();
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

libutil.popup.getbound = function(el, W, H, yd, dir){
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


libutil.popup.bpunds_intersect = function(popupbound, documenbound){
    var X0 =   popupbound.x < documenbound.x ? documenbound.x : popupbound.x;
    var Y0 =   popupbound.y < documenbound.y ? documenbound.y : popupbound.y;
    var X1 =   (popupbound.x + popupbound.width) < (documenbound.x + documenbound.width) ? 
        (popupbound.x + popupbound.width) : (documenbound.x + documenbound.width);
    var Y1 =   (popupbound.y + popupbound.height) < (documenbound.y + documenbound.height) ? 
        (popupbound.y + popupbound.height) : (documenbound.y + documenbound.height);;    
    
   return (X1-X0)*(Y1-Y0);
}


libutil.popup.finddirect = function(el, W, H, yd){
    var windowbound = {
        'x': 0, 
        'y': 0, 
        'width': window.innerWidth , 
        'height': window.innerHeight
    };
    var popupbound0 =  libutil.popup.getbound(el, W, H, yd,0);
    var popupbound1 =  libutil.popup.getbound(el, W, H, yd,1);
    var popupbound2 =  libutil.popup.getbound(el, W, H, yd,2);
    var popupbound3 =  libutil.popup.getbound(el, W, H, yd,3);
    var range = [libutil.popup.bpunds_intersect(popupbound2, windowbound),
    libutil.popup.bpunds_intersect(popupbound1, windowbound),
    libutil.popup.bpunds_intersect(popupbound3, windowbound),
    libutil.popup.bpunds_intersect(popupbound0, windowbound)];
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

libutil.popup.createsvgs = function(el, W, H, yd, dir, bodystyle, popupstyle){
    

    if ((dir==undefined) || (dir==null)) {
        dir = libutil.popup.finddirect(el, W, H, yd);
    }
    
    var bounds=libutil.popup.getbound(el, W, H, yd, dir);
    
    var h0 = parseFloat(el.getAttribute('height'));
    var w0 = parseFloat(el.getAttribute('width'));  
    
    var hh= h0 + 2*yd;
    var wh= w0 + 2*yd;
    
    var xc = bounds.x;
    var yc = bounds.y;
    var hc = bounds.height;
    var wc = bounds.width;
    
    var docelem = document.documentElement;
    
    var svg =libutil.svg.create_svg(docelem, xc , yc ,  hc , wc);
    
    libutil.svg.create_rect(svg, 0 , 0 ,  hc  , wc,  null , null , popupstyle ? popupstyle : 'fill: white; opacity: 0.0;', null);
    
    svg.popupbody = libutil.svg.create_svg(svg, dir==1 ? wh : 0 , dir==2 ? hh : 0 ,  H , W);
    
    libutil.svg.create_rect(svg.popupbody, 0 , 0 ,  H  , W,  null , null , bodystyle ?  bodystyle : 'fill: white; opacity: 1.0;', null);
    
    return svg;
}

// xslttransform


libutil.xslttransform.rootDocument = function (){ 
    if (window.__rootDocument)
        return window.__rootDocument;
    window.__rootDocument = libutil.document.readDoc(window.document.URL);
    return window.__rootDocument;
}


libutil.xslttransform.literootDocument = function (){ 
    if (window.__literootDocument){
        libutil.dom.clearChildNode(window.__literootDocument.documentElement);
        return window.__literootDocument;}
    window.__literootDocument = libutil.document.readDoc(window.document.URL);
    libutil.dom.clearChildNode(window.__literootDocument.documentElement);
    return window.__literootDocument;
}

//libutil.xslttransform.literootDocumentElement = function (){     
//    return libutil.xslttransform.literootDocument().documentElement;
//}


libutil.xslttransform.xsltDocument = function(){
    if (window.__xsltDocument)
        return window.__xsltDocument;    
    var root = libutil.xslttransform.rootDocument();
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
                        window.__xsltDocument = libutil.document.readDoc(urlxslt);
                    }
                }
            } 
        }
    }
    return window.__xsltDocument;
}

libutil.xslttransform.xsltProcessor = function(){
    if (window.__xsltProcessor) return window.__xsltProcessor;
    window.__xsltProcessor=new XSLTProcessor();
    var xsltdoc = libutil.xslttransform.xsltDocument();
    if (window.__xsltProcessor &&  xsltdoc)
        window.__xsltProcessor.importStylesheet(xsltdoc);
    else
        throw 'XSLT transform error';       
    return window.__xsltProcessor;
}


libutil.xslttransform.tranformDocument = function(doc){
    return libutil.xslttransform.xsltProcessor().transformToDocument(doc);
}

libutil.xslttransform.tranform_and_getById = function(doc, id){
    var transdoc = libutil.xslttransform.xsltProcessor().transformToDocument(doc);
    return transdoc.getElementById(id);
}


//  window

libutil.window.create = function(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate){
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


libutil.window.create_modal = function(url,  caption, value ,top, left, width, height, tooltip, allwaystop, nodecorate){
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
    libutil.global.setGlobalPropertyEditor({'value': value});
    window.showModalDialog(url, null , tmp);
    
    var ret = libutil.global.getGlobalPropertyEditor();
    if (!ret || ret==value) return null;
    libutil.global.setGlobalPropertyEditor();
    return ret;
}


libutil.window.createhtml = function(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, stylefile, style){
    var newwin=libutil.window.create(name , caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal);
    newwin.document.open();
    newwin.document.write('<?xml version="1.0" encoding="UTF-8"?>');
    newwin.document.write('<html>');
    newwin.document.write('    <head>');
    newwin.document.write('     <script type="text/javascript" src="../util/js/designer.js"></script>');
    newwin.document.write('     <script type="text/javascript" src="../util/js/libutil.js"></script>');
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

libutil.regex.check = function (value, expr){
    var re= new RegExp(expr);
    return re.test(value);
}

//


libutil.html.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS('http://www.w3.org/1999/xhtml', name);
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_html = function (parent, style){  
    var newel = libutil.html.create('html', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    return newel;
}


libutil.html.create_head = function (parent, style){  
    var newel = libutil.html.create('head', parent);
    if (!newel) return;
    if (parent) parent.appendChild(newel);
    if (style) 
        libutil.html.create_style(newel, style)
    return newel;
}

libutil.html.create_body = function (parent, style, classnm){
    var newel = libutil.html.create('body', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_tbody = function (parent, style, classnm){
    var newel = libutil.html.create('tbody', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_table = function (parent, style, classnm){
    var newel = libutil.html.create('table', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}


libutil.html.create_th = function (parent, style, classnm){
    var newel = libutil.html.create('th', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_tabel_header = function (tr, style, classnm, arr){
    for (var i=0; i < arr.length; ++i){
        var th = libutil.html.create_th(tr, style, classnm);
        th.innerHTML=arr[i];
    } 
}

libutil.html.create_tr = function (parent, style, classnm){
    var newel = libutil.html.create('tr', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_td = function (parent, style, classnm){
    var newel = libutil.html.create('td', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_div = function (parent, style, classnm){
    var newel = libutil.html.create('div', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_span = function (parent, style, classnm){
    var newel = libutil.html.create('span', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_link = function (parent, rel, type, href){
    var newel = libutil.html.create('link', parent);
    if (!newel) return;
    newel.setAttribute('rel', rel ? rel : 'stylesheet');
    newel.setAttribute('type', type ? type : 'text/css');
    if (href) newel.setAttribute('href', href);
    return newel;
}



libutil.html.create_style = function (parent,  style){
    
    var newel = libutil.html.create('style', parent);
    if (!newel) return;
    newel.setAttribute('type', 'text/css' );
    if (style) newel.innerHTML=style;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_button = function (parent, style, classnm, name, onclickfunc){
    var newel = libutil.html.create('button', parent);
    if (!newel) return;
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.className=classnm;
    if (name) newel.innerHTML=name;
    if (onclickfunc) newel.onclick=onclickfunc;
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.html.create_input = function (parent, type, value){
    var newel = libutil.html.create('input', parent);
    if (!newel) return;
    if (type) newel.setAttribute('type', type );
    if (value) {
        newel.setAttribute('value', value );
        newel.innerHTML=value;
    }
    return newel;
}

libutil.html.create_select = function (parent, type, value, list, addit){
    var newel = libutil.html.create('select', parent);
    if (!newel) return;
    if (type)
        newel.setAttribute('type', type );
    if (value) 
        newel.setAttribute('value', value );

    var newop = libutil.html.create('option', newel);
    newop.setAttribute('selected','');
    newop.innerHTML=value;

    for(var i=0; i < list.length; i++){
        if (list[i]!=value){
            var newop = libutil.html.create('option', newel);
            newop.innerHTML=list[i];
        }
    }
    if (addit){
        var newop = libutil.html.create('option', newel);
        newop.setAttribute('value', '...' );
        newop.innerHTML='...';
    }
    return newel;
}

libutil.html.create_tool = function (doc, nametool, names, hints, funcs, size, header, headerstyle){
    if (names){
        var body=doc.getElementsByTagName('body')[0];
        var result = {};
        if (body) {
            if (header){
                var divhead = libutil.html.create_div(body, headerstyle); 
                divhead.innerHTML=header;
            }
            libutil.html.create_tool_style(doc, nametool, names,  size);
            var div = libutil.html.create_div(body);
            div.setAttribute('class','toolbar');
            for (var i=0;i<names.length;++i){
                var btn = libutil.html.create_button( div,null,nametool+'-item toggleable '+names[i],'', (funcs && funcs.length > i) ? funcs[i] : null);               
                btn.namebtn=names[i];
                btn.nametool=nametool;
                if ( hints &&  hints.length>i)
                    btn.setAttribute('title', hints[i])
                var dv = libutil.html.create_div(btn,null,nametool+'-icon');
                if (hints &&  hints.length>i)
                    dv.setAttribute('title', hints[i]);
                result[names[i]] = btn;
            } 
            return result;
        }
    }
    return undefined;
} 



libutil.html.create_tool_style = function (doc, nametool, names,  sz){
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
        " background-image: url(../util/css/res/"+onfile+".png);}\n"+
        " \n"+
                  
        "."+nametool+"-item[disabled] ."+nametool+"-icon{\n"+
        " background-image: url(../util/css/res/"+disablefile+".png);}\n"+
        " \n"+

        "."+nametool+"-item:hover[disabled] ."+nametool+"-icon{\n"+
        " background-image: url(../util/css/res/"+disablefile+".png);}\n"+
        " \n"+

        "."+nametool+"-item[off] ."+nametool+"-icon{\n"+
        " background-image: url(../util/css/res/"+offfile+".png);}\n"+
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


    
        libutil.html.create_style(head, style);
    }
} 



///////////////////////////////////////////////

libutil.dom.clearChildNode = function (element){
    while (element.hasChildNodes()) 
        element.removeChild(element.lastChild);
}

libutil.dom.check_is_parent  = function(canparent,test,self){
     if (!test) return false;
     if (test==canparent) return (self) ? true : false;
     return libutil.dom.check_is_parent (canparent,test.parentNode,true);
}





///////////////////////////////////////////////



libutil.svg.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS('http://www.w3.org/2000/svg', name);
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.svg.create_svg = function (parent, x, y,  height, width, view){
    
    var newel = libutil.svg.create('svg', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));
    if (width || width==0) newel.setAttribute('width', parseFloat(width));
    if (height || height==0) newel.setAttribute('height', parseFloat(height));    
    if (view) newel.setAttribute('viewBox', view);
    return newel;
}

libutil.svg.create_g = function (parent){
    
    var newel = libutil.svg.create('g', parent);
    return newel;
}


libutil.svg.create_rect = function (parent, x, y,  height, width,  rx, ry, style, classnm){
    
    var newel = libutil.svg.create('rect', parent);
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

libutil.svg.create_circle = function (parent, x, y,  r,  style, classnm){
    
    var newel = libutil.svg.create('circle', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('cx', parseFloat(x));
    if (y || y==0) newel.setAttribute('cy', parseFloat(y));
    if (r || r==0) newel.setAttribute('r', parseFloat(r));
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.setAttribute('class', classnm);
    return newel;
}

libutil.svg.create_text = function (parent, x, y,  style, classnm, text){
    
    var newel = libutil.svg.create('text', parent);
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

libutil.svg.create_foreignObject = function (parent, x, y, height, width){
    
    var newel = libutil.svg.create('foreignObject', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));
    if (width || width==0) newel.setAttribute('width', parseFloat(width));
    if (height || height==0) newel.setAttribute('height', parseFloat(height));
    
    return newel;
}

libutil.svg.foriegn_text = function (parent, x, y, height, width, text, style){
    
    var newel = libutil.svg.create_foreignObject(parent, x, y, height, width);
    
    var body = libutil.html.create_body(newel, 'margin: 0px;  height: '+height+'px; ');
    
    var div = libutil.html.create_div(body, style + ' overflow: hidden;');
    
    var span = libutil.html.create_span(div, 'line-height: '+ height/2 + 'px;');
    
    var headertextnode=parent.ownerDocument.createTextNode(text);
    
    span.appendChild(headertextnode);
    

}


libutil.svg.create_header = function (parent, x, y,  height, width, rx, ry,  rectstyle, text, htmltextstyle){

    var newheadrect =  libutil.svg.create_rect( parent, 
        x, y,  height, width, rx , ry, rectstyle);


    
    newheadrect.onmouseout = function() {
        event.preventDefault();
        event.stopPropagation();
        return;
    } 
        
    
    var headersvg=libutil.svg.create_svg(parent, 
        x ,y, height, width);
   
   

    var headertext=libutil.svg.foriegn_text(headersvg, 0 , 0  , height, width ,text,
        htmltextstyle);
    
    return newheadrect;
    
}

libutil.svg.create_button = function (parent, x, y,  height, width, rx, ry,  rectstyle, rectclass,   text, textstyle){

    var headersvg=libutil.svg.create_svg(parent, 
        x,y, height, width);   

    var newheadrect =  libutil.svg.create_rect( headersvg, 
        0, 0,  height, width, rx , ry,  rectstyle, rectclass);
                                       
    headersvg.onmouseout = function() {
        event.preventDefault();
        event.stopPropagation();
        return;
    }                                        
                                       
                                
                                       
    var headertext=libutil.svg.create_text(headersvg,
        width / 2, height / 2, 
        textstyle,
        'central_svgnatext');

    
    var headertextnode=parent.ownerDocument.createTextNode(text);
    
    headertext.appendChild(headertextnode);
    
    return headersvg;                                    

    
}


//


libutil.www.create_window = function(doc, id, x, y, width, height, style){
    
    if (!doc) return undefined;

    var result = undefined; 
      

    if (doc){
        var root = doc.documentElement;
        if (root) {
     
            var result = libutil.svg.create_foreignObject(doc.documentElement,  x ? x : 0, y ? y : 0, height ? height : 300, width ? width : 300 );
            result.setAttribute('opacity', '0.9');
            result.setAttribute('id',id);
            
            var html = libutil.html.create_html(result);
            
            libutil.html.create_head(html,style);
            
            var body= libutil.html.create_body(html);
            
            var bodydiv= libutil.html.create_div(body);
           
            var divhd= libutil.html.create_div(bodydiv, null, 'scrollHeader');
            divhd.setAttribute('id', id+'_header');
            divhd.innerHTML=id;

            result.divhd = divhd;
            
            result.bindelement=bodydiv;
               
            return result;

        }
    }
    return undefined;
}

libutil.www.correct_window_height = function (win, innerheight){
    if (win.innerHeight!=innerheight){
        var correctH =  win.outerHeight + (innerheight - win.innerHeight);
        win.resizeTo(win.outerWidth,correctH);
    }
}

libutil.www.create_tbwindow = function (name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, names, hints,  funcs, destroyfunc){
    var tmp=libutil.global.getGlobal();
    if (tmp && !tmp[name]){
        tmp[name]=libutil.window.createhtml('_'+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, "../util/css/maintoolstyle.css");
        tmp[name].onunload= destroyfunc ? destroyfunc : 
        function(){     
            try{
                var tmpo=libutil.global.getGlobal();
                if (tmpo && tmpo[name])
                    tmpo[name]=undefined;
            }
            catch(error){}
        };
        if (names)    
            libutil.www.create_tbwindow_tools(name, null, names, hints, funcs);
        return tmp[name];
    }   
}

libutil.www.create_modalwindow = function (name, caption, top, left, width, height, tooltip, allwaystop, nodecorate){
    var result=libutil.window.libutil.window.create_modal(+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate);
    return result;
}

libutil.www.create_tbwindow_tools = function (name, tools, names, hints, funcs, size, header, headerstyle){
    var tmp=libutil.global.getGlobal();
    if (name && names && funcs && tmp[name]){
        if (!tools) tools=name;
        if (!tmp[name].tools)
            tmp[name].tools={};
        tmp[name].tools[tools]=libutil.html.create_tool(tmp[name].document, tools, names, hints, funcs, size, header, headerstyle) ;
        tmp[tools+'_tools']=tmp[name].tools[tools];
    }    
}

libutil.www.set_tbwindow_btnstatus = function (name, tools, btnname , state){
    var tmp=libutil.global.getGlobal();
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



libutil.alarmtable.prototype.execute = function(evnt) {
    this.cleartable();   
    this.fillrowtab(evnt);
}

libutil.alarmtable.prototype.cleartable = function() {
    var el = this.alarmelement;
    if (el==null) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    while (el.children.length>1)
        el.removeChild(el.lastChild);
}
        
          

  
libutil.alarmtable.prototype.fillrowtab = function(evnt){
    var el = this.alarmelement;
    if ((el==null) || (evnt==null)) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    for (var i=0;i<evnt.length;++i){
        this.insertrow(el, evnt[i]);
    }
     
}


libutil.alarmtable.prototype.insertrow = function(el, arr) {

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


libutil.document.readDoc = function (url){ 
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


libutil.document.writeDoc = function (doc){
    if (doc && dvnci_writefile){
        var xmls = new XMLSerializer();  
        var data= xmls.serializeToString(doc); 
        dvnci_writefile(doc.baseURI,data);
    }
}

libutil.document.findElementById = function (el, id){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.getAttribute('id')==id) return e;
        var result = libutil.document.findElementById(e, id);
        if (result) 
            return result;      
    }
}

libutil.document.findElementByTagName = function (el, name){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.localName==name) return e;
        var result = libutil.document.findElementByTagName(e, name);
        if (result) 
            return result;      
    }
}

// radactor util


///









  

    
