
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

libutil.geometry = {};

libutil.global = {};

libutil.error = {};

libutil.regex = {};

libutil.validator = {};

libutil.script = {};

libutil.LIB_NAMESPACE_URL =  'http://dvnci/lib';

libutil.SVG_NAMESPACE_URL =  'http://www.w3.org/2000/svg';

libutil.XHTML_NAMESPACE_URL =  'http://www.w3.org/1999/xhtml';

libutil.XLINK_NAMESPACE_URL =  'http://www.w3.org/1999/xlink';

libutil.XSLT_NAMESPACE_URL =  'http://www.w3.org/1999/XSL/Transform';

libutil.test = {};




libutil.alarmtable = function(el){
    
    this.alarmelement=libutil.dom.findElementByTagName(el,'table');
    if (this.alarmelement){
        this.alarmelement.alarlistener=this;
        this.alarmelement.onalarm=function(ev){
            this.alarlistener.execute(ev);
        }
    }
}


function formopen(name){
    if ((!window.$$editable) || ($$editable())) return;
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



function formclose(name){
    if ((!window.$$editable) || ($$editable())) return;
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



function formclose_win(){
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

function formclose_allwin(){
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
    if (window.$$global && window.$$global().___mainwindow){
        var win = window.$$global().___mainwindow;
        var unloadscript = !window.$$editable || !window.$$editable();
        if (unloadscript && win.___global___unload)
            win.___global___unload();
        win.onunload=function(){$$exit();}
        win.$$global().___mainwindow.close();
        win.$$global().___mainwindow=undefined;}
    else{
       $$exit();
       window.close();}
}




function init_project_controller(){
    libutil.global.getStartupDoc(document);   
    libutil.project.init_form();
    if (window.$$editable && window.$$editable() && dsutl.toolwin) 
        dsutl.toolwin.getMainWindow();
    var tmp = window.$$global ? window.$$global() : null;
    if (tmp){
        tmp['___mainwindow'] = window;}

}

//





libutil.util.remove_element_arr = function(arr,ind){
    for (var i=ind; i<arr.length-1;++i)
        arr[i]=arr[i+1];
    if (ind<arr.length) 
        arr.length=arr.length-1;
}


libutil.util.trim = function(str){
    return str.replace(/(^\s+)|(\s+$)/g, "");
}




//


libutil.global.getFormList = function (){
    if (window.$$global && !window.$$global().formlist)
        window.$$global().formlist=[];
    return window.$$global ? window.$$global().formlist : null;
}

libutil.global.getLibList = function (){
    if (window.$$global && !window.$$global().liblist)
        window.$$global().liblist=[];
    return window.$$global ? window.$$global().liblist : null;
}

libutil.global.getScriptList = function (){
    if (window.$$global && !window.$$global().scriptlist)
        window.$$global().scriptlist=[];
    return window.$$global ? window.$$global().scriptlist : null;
}

libutil.global.getStartupDoc = function (doc){
    if (window.$$global && !window.$$global().startupdocument && doc)
        window.$$global().startupdocument=doc;
    return window.$$global ? window.$$global().startupdocument : null;
}

libutil.global.getGlobalPropertyEditor = function (){
    return window.$$global ? window.$$global().globalpropertydialog : null;   
}

libutil.global.setGlobalPropertyEditor = function (val){
    if (window.$$global) 
        window.$$global().globalpropertydialog=val;   
}

//

libutil.startup.init = function(){
    var tmp  = window.$$global ? window.$$global() : null;
    if ((window.$$editable) && ($$editable())){
        document.red = new designer(document);
        libutil.project.add_design_style(document);
        libutil.startup.initdesigner(window.name, document.red);
        set_win_designer(window, document.red);
        if (tmp)
           tmp.currentred=document.red;
    }
    window.onunload=formclose_win;

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
            
            var tmp=$$global();
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
                
            libutil.project.setXSLTScriptList();     

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
    var tmp=$$global();
    var prjpath=tmp.projectPath;
    var path = prjpath && els.getAttribute('file') ? prjpath.toString() + els.getAttribute('file').toString() : 
    els.getAttribute('file') ? els.getAttribute('file').toString() : null;
    if (path){            
        var param = libutil.project.buildparam(els);
        var visible =((els.hasAttribute('visible')) && (els.getAttribute('visible')=='false')) ? false : true;
        if (visible) {
            var win=window.open(path, els.hasAttribute('name')  ? els.getAttribute('name') :  '', param);       
            win.document.domain=document.domain;
        } 
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
            'visible'  : visible,
            'element' : els
        });
    }   
}


libutil.project.add_design_style  = function(doc){
    if (doc.documentElement){
        var dstyle = ".designer_selected { opacity: 0.8 !important; outline: 1px solid #E00 !important;} \n"+
        "*[isgoupelement]{ outline: 1px dashed green !important; } \n"+
        'g[cursor="pointer"]:hover { outline: 0px solid transparent  !important;} \n'+
        'g[cursor="pointer"].designer_selected { opacity: 0.8 !important;  outline: 1px solid red !important;} \n'+
        "*[isgoupelement].designer_selected { opacity: 0.8 !important;  outline: 1px solid red !important;}\n"+
        "*[filter] { filter: url('') !important;} \n"+ 
        ".highlight-selected{ fill: none !important; stroke-width: 1 !important; stroke: red !important;}\n"+ 
        "*[dv-visible] { display: block !important;} \n";;
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
    var doc = libutil.dom.readDoc(path);
    if (doc){
        var els = doc.getElementsByTagNameNS(libutil.LIB_NAMESPACE_URL,'creator');        
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

libutil.project.getXSLTScriptElements = function(){
    var href="../util/scriptinclude.xsl";
    var doc = libutil.dom.readDoc(href);
    var root = doc.getElementById('scriptlist');
    return root;   
}

libutil.project.getXSLTScriptList = function(){
    var list=libutil.project.getXSLTScriptElements();
    if (list==null){
        console.error('Not find XSL liblist');
        return null;
    }      
    var result=[];
    if (list){        
        for(var e=list.firstChild; e; e=e.nextSibling){
            if ((e.getAttribute) && (e.localName=='call-template') && (e.getAttribute('name')=='lib_script_include_file')){
                for(var ep=e.firstChild; ep; ep=ep.nextSibling){
                if ((ep.getAttribute) && (ep.localName=='with-param') && (ep.getAttribute('name')=='file') && (ep.textContent!='')){
                   result.push({'file' : ep.textContent})
                }
            }
        }
    }  
}
return result;
}

libutil.project.setXSLTScriptList = function(){
   var tmp=$$global();
   if (tmp)   
       tmp.scriptlist = libutil.project.getXSLTScriptList();   
}

libutil.project.insertXSLTScriptList = function(file){
    var list=libutil.project.getXSLTScriptElements();
    if (list){
        for(var i=0; i < list.length; ++i){
            if (list[i].file==file)
                return false;
        }
        list = libutil.project.getXSLTScriptElements();
        for(var e=list.firstChild; e; e=e.nextSibling){
            if ((e.getAttribute) && (e.localName=='call-template') && (e.getAttribute('name')=='lib_script_include_file')){
                for(var ep=e.firstChild; ep; ep=ep.nextSibling){
                    if ((ep.getAttribute) && (ep.localName=='with-param') && (ep.getAttribute('name')=='file')){
                        if (ep.textContent=='' || !ep.textContent){
                                var newel = e.cloneNode(true);
                                newel.childNodes[1].textContent=file;
                                e.parentNode.appendChild(newel);
                                libutil.dom.writeDoc(newel.ownerDocument);
                                libutil.project.setXSLTScriptList();
                                return true;                       
                        }
                    }
                }
        }    
        }
    console.error('Not set XSL liblist');
    return false;
}
return null;
}

libutil.project.removeXSLTScriptList = function(file){
    if (file=='') return true;
    var list=libutil.project.getXSLTScriptElements();
    if (list){
        list = libutil.project.getXSLTScriptElements();
        for(var e=list.firstChild; e; e=e.nextSibling){
            if ((e.getAttribute) && (e.localName=='call-template') && (e.getAttribute('name')=='lib_script_include_file')){
                for(var ep=e.firstChild; ep; ep=ep.nextSibling){
                    if ((ep.getAttribute) && (ep.localName=='with-param') && (ep.getAttribute('name')=='file') && (ep.textContent==file)){
                        var parent = e.parentNode;
                        parent.removeChild(e);
                        libutil.dom.writeDoc(parent.ownerDocument);
                        libutil.project.setXSLTScriptList();
                        return true;
                    }
                }
            }                
        }
        console.error('Not remove XSL liblist');
        return false;
    }
    return null;
}


//

libutil.test.element = function(el){
   console.log(el);
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
    return {
        'x': xc, 
        'y': yc, 
        'width': wc , 
        'height': hc
    } 
}


libutil.popup.bpunds_intersect = function(popupbound, documenbound){
    var X0 =   popupbound.x < documenbound.x ? documenbound.x : popupbound.x;
    var Y0 =   popupbound.y < documenbound.y ? documenbound.y : popupbound.y;
    var X1 =   (popupbound.x + popupbound.width) < (documenbound.x + documenbound.width) ? 
    (popupbound.x + popupbound.width) : (documenbound.x + documenbound.width);
    var Y1 =   (popupbound.y + popupbound.height) < (documenbound.y + documenbound.height) ? 
    (popupbound.y + popupbound.height) : (documenbound.y + documenbound.height);

    return (popupbound.width>0 && popupbound.height>0) ? parseInt(((X1-X0)*(Y1-Y0)*1000)/(popupbound.height * popupbound.width)) : 0;
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
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 0;     
    }
    return 2;
}

libutil.popup.createsvgs = function(el, W, H, yd, dir, bodystyle, popupstyle, r){
    

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
    
    var svg =libutil.svg.create_element('svg', docelem, [{'name' : 'x', 'value': xc},
                                                         {'name' : 'y', 'value': yc},
                                                         {'name' : 'width', 'value': wc},
                                                         {'name' : 'height', 'value': hc}]);
    
    libutil.svg.create_element('rect', svg, [{'name' : 'x', 'value':  0},
                                             {'name' : 'y', 'value':  0},
                                             {'name' : 'width', 'value': wc},
                                             {'name' : 'height', 'value': hc},
                                             {'name' : 'style', 'value': popupstyle ? popupstyle : 'fill: white; opacity: 0.0;'}]);
    
    svg.popupbody = libutil.svg.create_element('svg', svg, [{'name' : 'x', 'value': dir==1 ? wh : 0},
                                                            {'name' : 'y', 'value':  dir==2 ? hh : 0},
                                                            {'name' : 'width', 'value': W},
                                                            {'name' : 'height', 'value': H}]);
    
    var rct = libutil.svg.create_element('rect', svg.popupbody , [{'name' : 'x', 'value':  0},
                                                        {'name' : 'y', 'value':  0},
                                                        {'name' : 'width', 'value': W},
                                                        {'name' : 'height', 'value': H},
                                                        {'name' : 'rx', 'value': r},
                                                        {'name' : 'ry', 'value': r},
                                                        {'name' : 'style', 'value': bodystyle ?  bodystyle : 'fill: white; opacity: 1.0;'}]);
    

    
    return svg;
}

// xslttransform


libutil.xslttransform.rootDocument = function (){ 
    if (window.__rootDocument)
        return window.__rootDocument;
    window.__rootDocument = libutil.dom.readDoc(window.document.URL);
    return window.__rootDocument;
}


libutil.xslttransform.literootDocument = function (){ 
    if (window.__literootDocument){
        libutil.dom.clearChildNode(window.__literootDocument.documentElement);
        return window.__literootDocument;
    }
    window.__literootDocument = libutil.dom.readDoc(window.document.URL);
    libutil.dom.clearChildNode(window.__literootDocument.documentElement);
    return window.__literootDocument;
}




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
                        window.__xsltDocument = libutil.dom.readDoc(urlxslt);
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
    libutil.global.setGlobalPropertyEditor({
        'value': value
    });
    window.showModalDialog(url, null , tmp);
    
    var ret = libutil.global.getGlobalPropertyEditor();
    if (!ret || ret==value) return null;
    console.log('return ' + ret)
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
    return expr.test(value);
}

//

//

libutil.geometry.boundrect = function (el){
    var box = el && el.getBBox ? el.getBBox() : null;
    var rect = box ? {'x' : box.x , 'y' : box.y , 'w' : box.width , 'h' : box.height} : null;
    if (rect) return rect;
    var boxs = el  && el.getClientRects ? el.getClientRects() : null;
    var box = boxs && boxs.length ? boxs[0] : null;
    return box ? {'x' : box.top , 'y' : box.left , 'w' : box.width , 'h' : box.height} : null;
}

//


libutil.html.create = function (name, parent){
    var newel = parent.ownerDocument.createElementNS(libutil.XHTML_NAMESPACE_URL, name);
    parent.appendChild(newel);
    return newel;
}

libutil.html.create_element = function (name, parent, attr){
    var newel = parent.ownerDocument.createElementNS(libutil.XHTML_NAMESPACE_URL, name);
    if (attr){
        for (var i=0; i < attr.length; ++i){
           if (attr[i].value) 
               newel.setAttribute(attr[i].name, attr[i].value); 
        }
    }
    if (parent)
        parent.appendChild(newel);
    return newel;
}


libutil.html.create_element_not_insert = function (name, parent, attr){
    var newel = parent.ownerDocument.createElementNS(libutil.XHTML_NAMESPACE_URL, name);
    if (attr){
        for (var i=0; i < attr.length; ++i){
           if (attr[i].value) 
               newel.setAttribute(attr[i].name, attr[i].value); 
        }
    }
    return newel;
}


libutil.html.create_tabel_header = function (tr, style, classnm, arr){
    for (var i=0; i < arr.length; ++i){
        var th = libutil.html.create_element('th', tr,  [{'name' : 'style', 'value': style},
                                                         {'name' : 'class', 'value': classnm}]);
        th.innerHTML=arr[i];
    } 
}


libutil.html.create_link = function (parent , href){
    var newel = libutil.html.create('link', parent);
    if (!newel) return;
    newel.setAttribute('rel', 'stylesheet');
    newel.setAttribute('type',  'text/css');
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
                var divhead = libutil.html.create_element('div' , body ,[{'name' : 'style' , 'value' : headerstyle}]); 
                divhead.innerHTML=header;
            }
            libutil.html.create_tool_style(doc, nametool, names,  size);
            var div = libutil.html.create_element('div' , body );
            div.setAttribute('class','toolbar');
            for (var i=0;i<names.length;++i){
                var btn = libutil.html.create_button( div,null,nametool+'-item toggleable '+names[i],'', (funcs && funcs.length > i) ? funcs[i] : null);               
                btn.namebtn=names[i];
                btn.nametool=nametool;
                if ( hints &&  hints.length>i)
                    btn.setAttribute('title', hints[i])
                var dv = libutil.html.create_element('div' , btn ,[{'name' : 'class' , 'value' : nametool+'-icon'}]);
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



libutil.svg.create = function (name, parent){
    if (!parent) return;
    var newel = parent.ownerDocument.createElementNS(libutil.SVG_NAMESPACE_URL, name);
    if (parent) parent.appendChild(newel);
    return newel;
}

libutil.svg.create_element = function (name, parent, attr){
    var newel = parent.ownerDocument.createElementNS(libutil.SVG_NAMESPACE_URL, name);
    if (attr){
        for (var i=0; i < attr.length; ++i){
           if (attr[i].value) 
               newel.setAttribute(attr[i].name, attr[i].value); 
        }
    }
    if (parent) 
        parent.appendChild(newel);
    return newel;
}

libutil.svg.create_element_no_insert = function (name, parent, attr){
    var newel = parent.ownerDocument.createElementNS(libutil.SVG_NAMESPACE_URL, name);
    if (attr){
        for (var i=0; i < attr.length; ++i){
           if (attr[i].value) 
               newel.setAttribute(attr[i].name, attr[i].value); 
        }
    }
    return newel;
}

libutil.svg.create_text = function (parent, x, y,  style, classnm, text){
    
    var newel = libutil.svg.create('text', parent);
    if (!newel) return;
    if (x || x==0) newel.setAttribute('x', parseFloat(x));
    if (y || y==0) newel.setAttribute('y', parseFloat(y));  
    if (style) newel.setAttribute('style', style);
    if (classnm) newel.setAttribute('class', classnm);
    newel.textContent=text;
    return newel;
}



libutil.svg.create_button = function (parent, x, y, width, height, rx, ry,  rectstyle, rectclass,   text, textstyle, textclass){

    var headersvg=libutil.svg.create_element('svg', parent , [{'name' : 'x', 'value': x},
                                                         {'name' : 'y', 'value': y},
                                                         {'name' : 'width', 'value': width},
                                                         {'name' : 'height', 'value': height}]);   

    libutil.svg.create_element('rect', headersvg, [{'name' : 'x', 'value':  0},
                                                {'name' : 'y', 'value':  0},
                                                {'name' : 'width', 'value': width},
                                                {'name' : 'height', 'value': height},
                                                {'name' : 'rx', 'value': rx},
                                                {'name' : 'ry', 'value': ry}, 
                                                {'name' : 'style', 'value': rectstyle},
                                                {'name' : 'class', 'value': rectclass}]);
                                    
                             
    libutil.svg.create_text(headersvg,
        width / 2, height / 2, 
        textstyle,
        'central_svgnatext ' +  textclass, text);

    
    return headersvg;                                    

    
}

libutil.svg.create_gradient = function (name ,parent, attr, colors){
    if (colors){
    var gradient=libutil.svg.create_element(name , parent , attr); 
    for (var i=0; i < colors.length; ++i){
        libutil.svg.create_element('stop', gradient , [{'name' : 'offset' , 'value' : colors[i].offset ? colors[i].offset : 0},
                                                       {'name' : 'stop-color' , 'value' : colors[i].stopcolor ? colors[i].stopcolor : '#000'}])
    }
    return gradient;
}
    return null;                                       
}


//


libutil.www.create_window = function(doc, id, x, y, width, height, style){
    
    if (!doc) return undefined;

    var result = undefined; 
      

    if (doc){
        var root = doc.documentElement;
        if (root) {
     
            var result = libutil.svg.create_element('foreignObject', doc.documentElement, [{'name' : 'id', 'value':  id},
                                                                                   {'name' : 'x', 'value':  x ? x : 0},
                                                                                   {'name' : 'y', 'value':  y ? y : 0},
                                                                                   {'name' : 'width', 'value': width ? width : 300},
                                                                                   {'name' : 'height', 'value': height ? height : 300}]);         
            var html = libutil.html.create_element('html' , result);
            
            libutil.html.create_element('head', html,[{'name' : 'style', 'value':  style}]);
            
            var body= libutil.html.create_element( 'body' ,html);
            
            var bodydiv= libutil.html.create_element('div' , body );
           
            
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
    var tmp=$$global();
    if (tmp && !tmp[name]){
        tmp[name]=libutil.window.createhtml('_'+name, caption, top, left, width, height, tooltip, allwaystop, nodecorate, modal, "../util/css/maintoolstyle.css");
        tmp[name].onunload= destroyfunc ? destroyfunc : 
        function(){     
            try{
                var tmpo=$$global();
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


libutil.www.create_tbwindow_tools = function (name, tools, names, hints, funcs, size, header, headerstyle){
    var tmp=$$global();
    if (name && names && funcs && tmp[name]){
        if (!tools) tools=name;
        if (!tmp[name].tools)
            tmp[name].tools={};
        tmp[name].tools[tools]=libutil.html.create_tool(tmp[name].document, tools, names, hints, funcs, size, header, headerstyle) ;
        tmp[tools+'_tools']=tmp[name].tools[tools];
    }    
}

libutil.www.set_tbwindow_btnstatus = function (name, tools, btnname , state){
    var tmp=$$global();
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
    var tr  = document.createElementNS(libutil.XHTML_NAMESPACE_URL,'tr');
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
                var sp = document.createElementNS(libutil.XHTML_NAMESPACE_URL,'span');
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

///////////////////////////////////////////////

libutil.dom.clearChildNode = function (element){
    if (element){
    while (element.hasChildNodes()) 
        element.removeChild(element.lastChild);
}}



libutil.dom.checkIsParent  = function(canparent,test,self){
    if (!test) return false;
    if (test==canparent) return (self) ? true : false;
    return libutil.dom.checkIsParent (canparent,test.parentNode,true);
}


libutil.dom.duplicateElement  = function(el, deep, excluteattr){
    var doc=el.ownerDocument ? el.ownerDocument : el.document;
    var namespace = el.namespaceURI;
    var localName = el.localName;
    //var parent=el.parentNode;
    var duplicate = doc.createElementNS(namespace, localName);
    
    var notexclude = function(nm){
        if (!excluteattr || !excluteattr.length) return true;
        for (var i=0;i<excluteattr.length;++i){
            if (excluteattr[i]==nm) return false;
        }
        return true;
    }
    
    for (var i=0;i<el.attributes.length;++i){
        if (notexclude(el.attributes[i].localName)){
        if (el.attributes[i].namespaceURI) 
            duplicate.setAttributeNS(el.attributes[i].namespaceURI , el.attributes[i].localName, el.attributes[i].value);
        else
            duplicate.setAttribute(el.attributes[i].localName, el.attributes[i].value);} 
    }
    
    if (deep || (deep==undefined)){
        for(var e=el.firstElementChild; e; e=e.nextElementSibling){
            duplicate.appendChild(e.cloneNode(true));
        }
    }
    
    return duplicate;
      
}


libutil.dom.findElementById = function (el, id){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.getAttribute('id')==id) return e;
        var result = libutil.dom.findElementById(e, id);
        if (result) 
            return result;      
    }
}

libutil.dom.findElementByTagName = function (el, name){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.localName==name) return e;
        var result = libutil.dom.findElementByTagName(e, name);
        if (result) 
            return result;      
    }
}

libutil.dom.findChildByTagName = function (el, name){
    for(var e=el.firstElementChild; e; e=e.nextElementSibling){
        if (e.localName==name) return e;    
    }
    return null;
}

libutil.dom.removeCild = function (parent, el){
    for(var e=parent.firstElementChild; e; e=e.nextElementSibling){
        if (e==el) {
            parent.removeChild(el);
            break;
        }
    }
}


libutil.dom.readDoc = function (url , text){ 
    try{
        var xmlHttp=new XMLHttpRequest();
        xmlHttp.open("GET",url,false);
        xmlHttp.send(null);
        return text ? xmlHttp.responseText : xmlHttp.responseXML;
    }
    catch(exception){
        alert(exception);
    }
    return null;
}


libutil.dom.writeDoc = function (doc){
    if (doc && window.$$writefile){
        var xmls = new XMLSerializer();  
        var data= xmls.serializeToString(doc); 
        $$writefile(doc.baseURI,data);
    }
}


/* 

  valdator

*/


libutil.validator.expresssion = function(val) {
    if ((val==undefined) || (val=='') || (val==null))  return undefined;
    var error = $$error(val);
    var test = $$check(val);
    return ((error===undefined) || (test===undefined)) ? undefined : (error==0);
    
}

libutil.validator.taglist = function(val) {
    if ((val==undefined) || (val=='') || (val==null))  return undefined;
    var error = $$error('tags('+val+')');
    var check = $$check('tags('+val+')');
    return (error===undefined) ? undefined : (error==0 && check);   
}

libutil.validator.tag = function(val) {
    if ((val==undefined) || (val=='') || (val==null))  return undefined;
    var error = $$error('tags('+val+')');
    var check = $$check(val+'.binding');
    return (error==undefined) ? undefined : (error==0 && (check!=undefined));   
}

libutil.validator.regex = function(val , regex) {
    if ((val==undefined) || (val=='') || (val==null))  return undefined;
    var error = val.test(regex);
    return (error==undefined) ? undefined : (error);   
}




  

    
