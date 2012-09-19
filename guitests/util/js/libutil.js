
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

libutil.proggress = {};

libutil.LIB_NAMESPACE_URL =  'http://dvnci/lib';

libutil.SVG_NAMESPACE_URL =  'http://www.w3.org/2000/svg';

libutil.XHTML_NAMESPACE_URL =  'http://www.w3.org/1999/xhtml';

libutil.XLINK_NAMESPACE_URL =  'http://www.w3.org/1999/xlink';

libutil.XSLT_NAMESPACE_URL =  'http://www.w3.org/1999/XSL/Transform';

libutil.test = {};







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
        win.onunload=function(){
            $$exit();
        }
        win.$$global().___mainwindow.close();
        win.$$global().___mainwindow=undefined;
    }
    else{
        $$exit();
        window.close();
    }
}




function init_project_controller(){
    libutil.global.getStartupDoc(document);
    try{
        var tmp=$$global();
        var projectPath=libutil.project.path_from_URL(document.URL);
        tmp.projectPath=projectPath;
        // var elp=libutil.global.getStartupDoc().getElementsByTagName('project')[0];
        //console.log(elp);
        //var projectPath=elp.getAttribute('path');
        //console.log(projectPath);
        $$global().loadwin = window.open(projectPath+ 'load.xml', 'initialisate' , 
            "caption=initialisate;left=0%;top=0%;width=100%;height=100%;decorated=no;allwaystop=yes");
        setTimeout(function(){
            libutil.project.init_form();
        }, 1000);
    }
    catch(error){
        console.error('init_project_controller error:',error);
        libutil.project.init_form();
    }
    
    if (window.$$editable && window.$$editable() && dsutl.toolwin) 
        dsutl.toolwin.getMainWindow();
    var tmp = window.$$global ? window.$$global() : null;
    if (tmp){
        tmp['___mainwindow'] = window;
    }

}

//





libutil.util.remove_element_arr = function(arr,ind){
    for (var i=ind; i<arr.length-1;++i)
        arr[i]=arr[i+1];
    if (ind<arr.length) 
        arr.length=arr.length-1;
}

libutil.util.insert_element_arr = function(arr, elem ,ind){
    if (arr.length==ind)
        arr.push(elem);
    arr.push(arr[arr.length-1])
    for (var i=arr.length-2; i> ind;--i){
        arr[i]==arr[i-1];
    }
    arr[ind] = elem;
}


libutil.util.trim = function(str){
    return str.replace(/(^\s+)|(\s+$)/g, "");
}

libutil.util.replacedelim = function(str){
    return str.replace(/^\:/, "_");
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
    if (window.$$global && doc)
        window.$$global().startupdocument=libutil.dom.readDoc(doc.URL);
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
    else{
        document.addEventListener('contextmenu' ,function () {
            event.stopPropagation();
            event.preventDefault();  
        });  
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

libutil.project.path_from_URL = function(url){
    //alert(url);
    var pathpos=url.search(/start\.xml/);
    if (pathpos<0) return null;
    //alert(url.substring(0,pathpos));
    return url.substring(0,pathpos);   
}

libutil.project.init_form = function(){
    var doc = libutil.global.getStartupDoc();
    if (doc){
        try{
                                   
            //var tmp=$$global();
            //var projectPath=libutil.project.path_from_URL(document.URL);
            
            //tmp.projectPath=projectPath;
            
            var els=doc.getElementsByTagName('form');                                 
            var ellib=doc.getElementsByTagName('lib');
                                          
            if (els)
                for (var i=0; i<els.length;++i)   
                    libutil.project.addtoformlist(els[i]);
                          
            if (ellib)  {     
                for (var i=0; i<ellib.length;++i)
                    libutil.project.addtoliblist(ellib[i],i);
            }
                
            if ($$global().loadwin) setTimeout(function(){
                $$global().loadwin.close()
            }, 2500);                
                

            
                
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

    var file =  els.getAttribute('file');
    var path = tmp.projectPath && file ? tmp.projectPath.toString() + file.toString() : null;
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
        "*[ismaybeinvisible]{ outline: 1px dashed yellow !important; } \n"+
        "*[isinvisibleelement]{ outline: 1px solid green !important; } \n"+
        'g[cursor="pointer"]:hover { outline: 0px solid transparent  !important;} \n'+
        'g[cursor="pointer"].designer_selected { opacity: 0.8 !important;  outline: 1px solid red !important;} \n'+
        "*[isgoupelement].designer_selected { opacity: 0.8 !important;  outline: 1px solid red !important;}\n"+
        "*[isinvisibleelement].designer_selected { opacity: 0.8 !important;  outline: 1px solid red !important;}\n"+
        "*[filter] { filter: url('') !important;} \n"+ 
        ".highlight-selected{ fill: none !important; stroke-width: 1 !important; stroke: red !important;}\n"+ 
        ".design_captured {display: block !important;}\n"+ 
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
                        result.push({
                            'file' : ep.textContent
                        })
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

libutil.popup.createsvgs = function(el, W, H, yd, dir, bodystyle, popupstyle, r , shift){
    

    if ((dir==undefined) || (dir==null)) {
        dir = libutil.popup.finddirect(el, W, H, yd);
    }
    
    var bounds=libutil.popup.getbound(el, W, H, yd, dir);
    

    
    var h0 = parseFloat(el.getAttribute('height'));
    var w0 = parseFloat(el.getAttribute('width'));
    
    if (shift){
        bounds.x = bounds.x + shift.left;
        bounds.y = bounds.y + shift.top;
    }
    
    var hh= h0 + 2*yd;
    var wh= w0 + 2*yd;
    
    var xc = bounds.x;
    var yc = bounds.y;
    var hc = bounds.height;
    var wc = bounds.width;
    
    var docelem = document.documentElement;
    
    var svg =libutil.svg.create_element('svg', docelem, [{
        name : 'x', 
        value: xc
    },

    {
        name : 'y', 
        value: yc
    },

    {
        name : 'width', 
        value: wc
    },

    {
        name : 'height', 
        value: hc
    }]);
                                                     
                                                    
    
    svg.hoverrect = libutil.svg.create_element('rect', svg, [{
        name : 'x', 
        value:  0
    },

    {
        name : 'y', 
        value:  0
    },

    {
        name : 'width', 
        value: wc
    },

    {
        name : 'height', 
        value: hc
    },

    {
        name : 'rx', 
        value: r
    },

    {
        name : 'ry', 
        value: r
    },                                             

    {
        name : 'style', 
        value: popupstyle ? popupstyle : 'fill: white; opacity: 0.0;'
    }]);
    
    svg.popupbody = libutil.svg.create_element('svg', svg, [{
        name : 'x', 
        value: dir==1 ? wh : 0
    },

    {
        name : 'y', 
        value:  dir==2 ? hh : 0
    },

    {
        name : 'width', 
        value: W
    },

    {
        name : 'height', 
        value: H
    }]);
    
    var rct = libutil.svg.create_element('rect', svg.popupbody , [{
        name : 'x', 
        value:  0
    },

    {
        name : 'y', 
        value:  0
    },

    {
        name : 'width', 
        value: W
    },

    {
        name : 'height', 
        value: H
    },

    {
        name : 'rx', 
        value: r
    },

    {
        name : 'ry', 
        value: r
    },

    {
        name : 'style', 
        value: bodystyle ?  bodystyle : 'fill: white; opacity: 1.0;'
    }]);
                                                    
    svg.boundspopup = {
        x: xc , 
        y: yc, 
        width: wc, 
        height: hc
    };                                                
    
    svg.buttonposition = {
        x : dir==3 ? W : 0, 
        y :  dir==0 ? H : 0, 
        width: (dir==0 || dir==2) ? W  : wh ,   
        height: (dir==1 || dir==3) ? H : hh , 
        dir : dir
    };
    //console.log('svg.buttonposition', svg.buttonposition);

    
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
        value: value
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

libutil.regex.add_postfix_file = function (value, expr){
    return value.substring(0,value.length-4)+expr+value.substring(value.length-4);
}

//

//

libutil.geometry.boundrect = function (el){
    var box = el && el.getBBox ? el.getBBox() : null;
    var rect = box ? {
        x : box.x , 
        y : box.y , 
        w : box.width , 
        h : box.height
    } : null;
    if (rect) return rect;
    var boxs = el  && el.getClientRects ? el.getClientRects() : null;
    var box = boxs && boxs.length ? boxs[0] : null;
    return box ? {
        x : box.top , 
        y : box.left , 
        w : box.width , 
        h : box.height
    } : null;
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
        var th = libutil.html.create_element('th', tr,  [{
            name : 'style', 
            value: style
        },

        {
            name : 'class', 
            value: classnm
        }]);
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
                var divhead = libutil.html.create_element('div' , body ,[{
                    name : 'style' , 
                    value : headerstyle
                }]); 
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
                var dv = libutil.html.create_element('div' , btn ,[{
                    name : 'class' , 
                    value : nametool+'-icon'
                }]);
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

    var headersvg=libutil.svg.create_element('svg', parent , [{
        name : 'x', 
        value: x
    },

    {
        name : 'y', 
        value: y
    },

    {
        name : 'width', 
        value: width
    },

    {
        name : 'height', 
        value: height
    }]);   

    libutil.svg.create_element('rect', headersvg, [{
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
        value: height
    },

    {
        name : 'rx', 
        value: rx
    },

    {
        name : 'ry', 
        value: ry
    }, 

    {
        name : 'style', 
        value: rectstyle
    },

    {
        name : 'class', 
        value: rectclass
    }]);
                                    
                             
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
            libutil.svg.create_element('stop', gradient , [{
                name : 'offset' , 
                value : colors[i].offset ? colors[i].offset : 0
            },

            {
                name : 'stop-color' , 
                value : colors[i].stopcolor ? colors[i].stopcolor : '#000'
            }])
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
     
            var result = libutil.svg.create_element('foreignObject', doc.documentElement, [{
                name : 'id', 
                value:  id
            },

            {
                name : 'x', 
                value:  x ? x : 0
            },

            {
                name : 'y', 
                value:  y ? y : 0
            },

            {
                name : 'width', 
                value: width ? width : 300
            },

            {
                name : 'height', 
                value: height ? height : 300
            }]);         
            var html = libutil.html.create_element('html' , result);
            
            libutil.html.create_element('head', html,[{
                name : 'style', 
                value:  style
            }]);
            
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


///////////////////////////////////////////////

libutil.alarmtable = function(el){
    try{
        this.alarmelement=libutil.dom.findElementByTagName(el,'table');
        if (this.alarmelement){
            var ts = this;
            this.handler = function(){
                ts.execute(event);
            }
            var rslt = window.addAlarmsListener(this.handler);
            this.init= rslt;
            if (!this.init){
                console.error('AlarmsListener didnt add');
                this.handler=undefined;
                return false;
            }
        }
    }
    catch(error){
        console.error('Alarms set error: ' + error );
    }
    return this.init;
}

libutil.alarmtable.prototype.detach = function() {
    if (this.handler)
        if (!window.removeAlarmsListener(this.handler))
            console.error('AlarmsListener didnt remove');
}

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
    if (!arr.kvit){
        tr.setAttribute("class", (arr.level>2) ? "avaron" : ((arr.level>1) ? "alarmon" : "noticeon"));
    }
    else{
        tr.setAttribute("class", (arr.level>2) ? "avarkvit" : ((arr.level>1) ? "alarmkvit" : "noticekvit"));
    }

      
  
    var td = document.createElement('td');
    
    //var tm= new Date(0,0,0, arr.time.getHours() ,arr.time.getMinutes() 
    //    +arr.time.getTimezoneOffset(),arr.time.getSeconds());
    var ta = document.createTextNode(arr.time.toLocaleTimeString());
    var sp = document.createElementNS(libutil.XHTML_NAMESPACE_URL,'span');
    sp.setAttribute("class", "smallfont");
    sp.appendChild(ta);
    td.appendChild(sp);
    tr.appendChild(td);
    
    
    td = document.createElement('td');
    
    ta = document.createTextNode(arr.tag);
    sp = document.createElement('span');
    sp.setAttribute("class", "smallfont");
    sp.appendChild(ta);
    td.appendChild(sp);
    tr.appendChild(td);
    
    td = document.createElement('td');
    
    ta = document.createTextNode(arr.message);
    sp = document.createElement('span');
    sp.setAttribute("class", "smallfont");
    sp.appendChild(ta);
    td.appendChild(sp);
    tr.appendChild(td);    
 
    el.appendChild(tr);
}

///////////////////////////////////////////////



libutil.trendchart = function(option){
    Highcharts.setOptions({
        global: {
            useUTC: false
        }
    });
    

    var elid=undefined;
    var throbid=undefined;    
    var width=undefined;
    var height=undefined;
    var colors=undefined;
    var r=undefined;
    var tags=undefined; 
    var sqlreq = undefined;  
    var start = undefined;  
    var stop = undefined;  
    var hist = undefined;
    var callback=undefined;
    var linewidth = 1;
    var axiswidth = 0.5;
    var axisXcolor=undefined;
    var axisYcolor=undefined;    
    var shadow = false;
    var animation = false;
    var defaultseriestype = undefined;
    var title = undefined;
    var fontsize = undefined;
    
    this.ranges={};

    
    var backgroundcolor = {
        linearGradient: ['100%', '0%', '100%', '100%'],
        stops: [
        [0, '#DDD'],
        [0.5, '#FFF'],
        [1, '#AAA']]
    };
    
    var disablecolor = "#777";  
 
    
    if (option){
        if (option.constructor == Object){
            for(var key in option) {
                switch(key){
                    case 'background':{
                        if (option[key].constructor == Array){
                            backgroundcolor = {
                                linearGradient: ['100%', '0%', '100%', '100%'],
                                stops: option[key]
                            }
                        }
                        if (option[key].constructor == String){
                            backgroundcolor = option[key]
                        }
                        break;
                    }
                    case 'element':{
                        elid = option[key];    
                        break;     
                    }
                    case 'throbler':{
                        throbid = option[key];    
                        break;     
                    }                    
                    case 'animation':{
                        animation = option[key];    
                        break;     
                    }
                    case 'lineWidth':{
                        linewidth = parseInt(option[key]);    
                        break;     
                    }
                    case 'axisWidth':{
                        axiswidth = parseInt(option[key]);    
                        break;     
                    }   
                    case 'axisColor':{
                        axisYcolor = option[key];   
                        break;     
                    }
                    case 'axisXColor':{
                        axisXcolor = option[key];   
                        break;     
                    }                      
                    case 'shadow':{
                        shadow = option[key];    
                        break;     
                    }  
                    case 'seriestype':{
                        defaultseriestype = option[key];    
                        break;     
                    }  
                    case 'disableColor':{
                        disablecolor = option[key];    
                        break;     
                    } 
                    case 'title':{
                        title = option[key];    
                        break;     
                    } 
                    case 'width':{
                        width = option[key].valueOf();    
                        break;     
                    } 
                    case 'height':{
                        height  = option[key];    
                        break;     
                    }
                    case 'r':{
                        r  = option[key];    
                        break;     
                    } 
                    case 'start':{
                        start  = option[key];    
                        break;     
                    }
                    case 'stop':{
                        stop  = option[key];    
                        break;     
                    } 
                    case 'hist':{
                        hist  = option[key];    
                        break;     
                    }  
                    case 'connection':{
                        sqlreq  = option[key];    
                        break;     
                    }
                    case 'callback':{
                        callback  = option[key];    
                        break;     
                    }      
                    case 'complete':{
                        this.complete  = option[key];    
                        break;     
                    }                  
                    case 'colors':{
                        if (option[key].constructor == Array){     
                            colors  = option[key];
                        }    
                        break;     
                    }
                    case 'ranges':{
                        this.ranges  = option[key];   
                        break;     
                    }                 
                    case 'tags':{
                        if (option[key].constructor == Array){     
                            tags  = option[key];
                        }    
                        break;     
                    }                 
                }
            }        
        }
    }

    this.callback=callback;
    this.sort(tags,colors);
    if (start || stop)
        hist={
            start: start, 
            stop: stop
        };
             
    
    try{
        if ((!window.$$editable) || ($$editable())) return;
        this.elid = elid;
        this.element = document.getElementById(elid);
        this.thtobblerbody = document.getElementById(throbid);
        if (this.element){
            if (this.thtobblerbody)
                this.element.trobbler = new libutil.proggress.throbber(this.thtobblerbody);
            this.sqlreq = sqlreq;
            if (tags.length){
            
                if (!this.sqlreq){
                    if (!hist) hist=0;
                    this.period = hist * 1000;
                }
                else{
                    this.start=hist.start;
                    this.stop=hist.stop;
                }
        
                var ts = this;
        

                this.disablecolor = disablecolor ? disablecolor : "#AAA";
                this.backgroundcolor = backgroundcolor ? backgroundcolor : "#EEE";
                this.axisYcolor = axisYcolor!==undefined ? axisYcolor : undefined;
                this.axisXcolor = axisXcolor!==undefined ? axisXcolor : this.axisYcolor;
        
                this.width = width;
                this.height = height;
                this.linewidth = linewidth ? linewidth : 1;
                this.axiswidth = axiswidth ? axiswidth : 1;
        
                var minBound = height < width ? height : width;
        
                this.fontsize = fontsize ? fontsize : (minBound ? parseInt(minBound / 30) : undefined );
        
                if (this.fontsize < 8) this.fontsize=8;
                this.shadow = shadow ? true : false;
                this.borderRadius = (r || r==0) ? r : 5;

                this.defaultseriestype =  defaultseriestype ? defaultseriestype : 'line';
        
                this.animation = animation ? true : false;
                this.title=title ? title : null;
        
        
                this.last_datastate = [];
                this.serias_lastvalue = [];
        
        
                this.null_datastate = [];
                this.null_datachange = false;
                this.null_periods = [];
                this.null_lines = [];
                //this.null_lines_change = false;
        
                this.current_null_periods = null;
                this.current_null_periods_change = false;
       
                for (var i=0;i<tags.length;++i){
                    this.null_datastate[i]=null;
                    this.last_datastate[i]=null;
                    this.serias_lastvalue[i]=null;
                }
        
                this.handler = function(){
                    ts.execute(event);
                }
        
                if (!sqlreq)
                    var rslt = this.element.addTrendsListener( this.handler, tags, this.period + libutil.trendchart.WAITDELT );
                else{
                    this.connection = sqlreq;
                    var rslt = this.connection.select_trends(this.handler,tags ,hist.start , hist.stop );         
                }  
        
        
                this.init = rslt;
                if (!this.init){
                    console.error('TrendsListener didnt set');
                    this.handler=undefined;
                }
                else{
            
                    var removeroot = function(){
                        //console.log('Remove graph root');
                        ts.detach();             
                    }
                    this.element.addEventListener('DOMNodeRemovedFromDocument',removeroot, false);
                }
            }
        }
        else {
            console.error('Not find trend element');
        }
    }
    catch(error){
        console.error('Trends set error: ' + error );
    }
}

libutil.trendchart.WAITDELT = 6000;

libutil.trendchart.prototype.sort = function(tags,colors){
    if (!tags || !colors || tags.constructor != Array){
        this.tags = tags;     
        this.colors = colors;
        return;
    };
    var tmp = [];
    for (var i=0; i<tags.length;++i){
        tmp.push({
            tag: tags[i], 
            color: colors.length>i ? colors[i]: 'red'
        });
    }
    tmp.sort(function(x1,x2){
        return x1.tag<x2.tag ? -1 : (x1.tag>x2.tag) ? 1 : 0
    });
    this.tags=[];
    this.colors=[];
    for (var i=0; i<tmp.length;++i){
        this.tags.push(tmp[i].tag);
        this.colors.push(tmp[i].color);
    }
}

libutil.trendchart.prototype.detach = function() {
    if (this.handler && !this.sqlreq)
        if (!this.element.removeTrendsListener(this.handler))
            console.error('TrendsListener didnt remove');
    if (this.chart)
        this.chart.destroy();
    this.element.chart=undefined;
}

libutil.trendchart.prototype.currentStart = function() {
    return this.sqlreq ? this.start.valueOf() : (new Date() - this.period).valueOf() ;
} 

libutil.trendchart.prototype.add_nullperiod =function (period){
    var start = period.start;
    var stop = period.stop;    
    for (var i=0;i<this.null_periods.length;++i){
        var state = (stop < this.null_periods[i].start) ? 0 :
        (((stop <= this.null_periods[i].stop) || (start <= this.null_periods[i].stop)) ? 1 : 2);
        //if (stop>this.null_periods[i].stop)        
        switch(state) {
            case 0:  {
                
                libutil.util.insert_element_arr(this.null_periods,period,i);
                this.null_datachange=true;
                //console.log('periods 0 : ' , this.null_periods, ' add ' , period);
                return;
            }
            case 1:  {
                
                this.null_periods[i].start = start < this.null_periods[i].start ? start : this.null_periods[i].start;
                this.null_periods[i].stop = stop > this.null_periods[i].stop ? stop : this.null_periods[i].stop;
                //console.log('periods 1 : '  , this.null_periods, ' change ' + i , this.null_periods[i]);
                this.null_datachange=true;
                return;
            }
        }                   
    }
    this.null_datachange=true; 
    this.null_periods.push(period);
   
}

libutil.trendchart.prototype.update_null_data =function (){

    if (this.current_null_periods_change){
        if (this.current_null_periods){
            this.chart.xAxis[0].removePlotBand('currentnulldata');  
            this.chart.xAxis[0].addPlotBand({
                from : this.current_null_periods.start , 
                to : Number.POSITIVE_INFINITY,
                color : this.disablecolor,
                id: 'currentnulldata'
            });
        }
        else{
            this.chart.xAxis[0].removePlotBand('currentnulldata');
        } 
        this.current_null_periods_change=false;      
    }
  
    if (this.null_datachange){
        //console.log('this.addBound() lines' , this.null_lines );
        this.addBound();  
        this.null_datachange =false;  
    }
}


libutil.trendchart.prototype.update_data =function (){
    var now = this.currentStart();
    var updated = false;

    for (var i=0; i<this.element.chart.series.length; ++i){
        if (this.element.chart.series[i].data.length) {
            //console.log( 'now:' + new Date(now) + ' data:' + new Date(this.element.chart.series[i].data[0].x));
            if (this.element.chart.series[i].data[0].x< now) {
                while((this.element.chart.series[i].data.length>1) && (this.element.chart.series[i].data[1].x<now))
                    this.element.chart.series[i].data[0].remove(false,false);
                if (this.element.chart.series[i].data[0].x< now){
                    var val = this.element.chart.series[i].data[0];
                    var valnext = (this.element.chart.series[i].data.length>1) ? this.element.chart.series[i].data[0] : null;
                    var yval = (val.y!==null) && (valnext.y!==null) ? ((valnext.y/* + val.y*/)/* / 2*/) : val.y;
                    val.x= now;
                    val.y= yval;
                    this.element.chart.series[i].data[0].update(val);
                }                               
                updated = true;             
            }
        }
    }
    var haschange = true;
    var periodhaschange = false;
    while (haschange){
        var haschange = false;
        if (this.null_periods.length && this.null_periods[0].stop<now){
            periodhaschange=true;
            libutil.util.remove_element_arr(this.null_periods,0);
            this.null_datachange = true;
            haschange = true;
            updated = true;
        }         
    }
    if (periodhaschange){
        haschange = false;
        if (this.null_lines.length && this.null_lines[0].time<now){
            libutil.util.remove_element_arr(this.null_lines,0);
            haschange = true;
        } 
    }
    return updated;
}



libutil.trendchart.prototype.checkdata =function (arr, val, i ,init, close){
    val[0]=val[0].valueOf();
    if (val[1]!=val[1] || val[1]===null || val[1]===undefined)
        val[1]=null;
    if (init){
        var now = this.currentStart();
        if (now<val[0]){
            if (val[1]===null){
                arr.push({
                    x : now, 
                    y : null
                });
                this.current_null_periods_change=true;
                this.null_datastate[i]=now;
                this.current_null_periods ={
                    'start' : now, 
                    'counter' : 1
                };  
                this.current_null_periods_change=true;
            }
            else
            {
                arr.push({
                    x : now, 
                    y : val[1]
                });            
            }
        }
        else{
            val[0]=now;    
        }
    }  
    
    if (!this.null_datastate[i] && (val[1]===null)){
        
        this.null_datastate[i]=/*this.last_datastate[i] ? this.last_datastate[i] :*/ val[0];
        
        this.null_lines.push({
            time : this.null_datastate[i] ,
            color : (this.colors && this.colors.length>i) ? this.colors[i] : 'black'
        });

        
        if (this.current_null_periods==null){
            this.current_null_periods_change=true;
            this.current_null_periods ={
                'start' : this.null_datastate[i], 
                'counter' : 1
            };     
        }
        else{
            if ((!arr) && (this.null_datastate[i] < this.current_null_periods.start)){
                
                this.current_null_periods.start =  this.null_datastate[i];
                console.log('add nullcouter this case' +this.current_null_periods.counter)
            }   
            this.current_null_periods.counter += 1;
        }
        
        this.current_null_periods_change=true;
        if (this.serias_lastvalue[i]!==null && arr){
            arr.push({
                x : val[0]-1, 
                y : this.serias_lastvalue[i]
            });
        } 
        console.log('new nullperiod: ' +new Date(this.null_datastate[i], val[1]))
         
    }
    else{
        if (this.null_datastate[i] && (val[1]!==null || close)){
            
            this.null_lines.push({
                time : val[0] , 
                color : (this.colors && this.colors.length>i) ? this.colors[i] : 'black'
            });

            
            this.add_nullperiod({
                start : this.null_datastate[i] , 
                stop : val[0]
            })
            //console.log('add nullperiod: ',new Date(this.null_datastate[i]),new Date(val[0]));
            this.null_datastate[i]=null;
            if ((this.current_null_periods!=null)){
                this.current_null_periods.counter-=1;
                //console.log('rem nullcouter: ' +this.current_null_periods.counter)
                if (!this.current_null_periods.counter){
                    
                    this.current_null_periods = null;
                }
            }
            this.current_null_periods_change=true;
        } 
    }
    if (val[1]!==null)
        this.serias_lastvalue[i]=val[1];
    this.last_datastate[i]=val[0];
    if (arr) 
        arr.push({
            x : val[0], 
            y : val[1]
        });
    else
        return {
            x : val[0], 
            y : val[1]
        };
}


libutil.trendchart.prototype.addBound =function (){
    this.chart.xAxis[0].removePlotBand();
    this.chart.xAxis[0].removePlotLine();
    //console.log('lines count:' , this.null_lines.length, 'bounds count:' , this.null_periods.length );
    for (var i = 0 ; i < this.null_periods.length; i++){
        this.chart.xAxis[0].addPlotBand({
            from : this.null_periods[i].start , 
            to : this.null_periods[i].stop,
            color : this.disablecolor
        });
    }
    
    for (var i = 0 ; i < this.null_lines.length; i++){
        this.chart.xAxis[0].addPlotLine({
            value : this.null_lines[i].time , 
            width : 1,
            color : /*this.null_lines[i].color*/'#EEE'
        });
    } 
//this.current_null_periods_change=false;
}





libutil.trendchart.prototype.startSeries = function(ev) {
    var series = [];
    for (var i=0;i<ev.length;++i){
        if (ev[i].data){
            var item = {
                id: this.elid+'___'+ev[i].name,
                name: ev[i].comment ? ev[i].comment : '_______', 
                yAxis: i,
                data : [],
                marker: {
                    enabled: false,
                    states: {
                        hover: {
                            enabled: false
                        }
                    }
                }
            }
        };
        if (this.start) 
            this.checkdata(item.data, [this.start, undefined] ,i, true);        
        for (var j = 0 ; j < ev[i].data.length; j++) { 
            var dt = ev[i].data[j];
            this.checkdata(item.data, dt,i,(j==0 && !this.start));
        }
        if (this.stop) 
            this.checkdata(item.data, [this.stop, undefined] ,i, false , true);
        series.push(item);
    }
    return series;
}




libutil.trendchart.prototype.addSeries = function(ev){
    var updated = false;
    for (var i=0;i<ev.length;++i)
        if (ev[i].data){
            for (var j = 0 ; j < ev[i].data.length ; j++) {
                var dt = ev[i].data[j];
                //if (((parseInt(dt[0].getMinutes() /1)) % (4)) ==i)
                //        dt[1]=null;
                dt = this.checkdata(null, dt,i)    
                this.element.chart.series[i].addPoint([dt.x , dt.y], false , false , false);
                updated = true;
            }
        }						

    var updated2 = this.update_data();
    var updated1 = this.update_null_data();
    if (updated || updated1 || updated2)
        this.element.chart.redraw();
        
}


libutil.trendchart.prototype.YAxis = function(){
    var rslt =[];
    for (var i=0;i<this.tags.length;++i){
        rslt.push({
            gridLineWidth : this.axiswidth,
            gridLineColor: this.axisYcolor,
            minPadding: 0.0,
            maxPadding: 0.0,
            min: this.ranges && this.ranges[this.tags[i]] ? this.ranges[this.tags[i]].min : null,
            max: this.ranges && this.ranges[this.tags[i]] ? this.ranges[this.tags[i]].max : null,            
            labels: {
                formatter: function() {
                    return this.value;
                },

                style:  {
                    color: this.colors ? this.colors[i] : undefined,
                    'font-size' : this.fontsize ? this.fontsize : undefined
                }
            },
            title: {
                text: null
            },    
            opposite: i ?  true : false
        });
    }
    return rslt;
}


libutil.trendchart.prototype.execute = function(ev) {
    if (this.callback)
        this.callback(ev);
    if (ev && (ev.length)){
        var ts =this;
        var elem=this.element;

        if ((elem!=null) && (ev.length)){
            
            if (elem.chart==null){
                
                if (this.element.trobbler)
                    this.element.trobbler.destroy();
                   
                this.chart = new Highcharts.Chart({
                    chart: {
                        width: this.width ? this.width : undefined,
                        height: this.height ? this.height : undefined,
                        renderTo: elem.id ,
                        defaultSeriesType: this.defaultseriestype,
                        backgroundColor: this.backgroundcolor,
                        animation: this.animation,
                        //type: 'spline'
                        zoomType: this.sqlreq ? 'xy' : undefined
                        

                    },
                    

                    title: {
                        text:  this.title,
                        style:{
                            'font-size' : '11px'
                        },
                        align: 'left',
                        x: 5,
                        verticalAlign: 'top',
                        y: 5
                    },
                    xAxis: {
                        type: 'datetime',
                        plotBands: [],
                        gridLineWidth : this.axiswidth,
                        gridLineColor: this.axisXcolor,
                        labels: {
                            style:  {
                                'font-size' : this.fontsize ? this.fontsize : undefined
                            }
                        }
                       
                    },
                    yAxis: this.YAxis(),
                    tooltip: {
                        borderRadius: this.borderRadius,
                        formatter: function() {
                            return '<b>'+ this.series.name +'</b><br/>'+
                            Highcharts.dateFormat('%H:%M:%S', this.x) +'<br/>'+ 
                            Highcharts.numberFormat(this.y, 2);
                        }
                    },
                    legend: {
                        enabled: false
                    },
                    exporting: {
                        enabled: false
                    },
                    credits: {
                        enabled: false
                    },  

                    plotOptions: {
                        line: {
                            allowPointSelect: false,
                            lineWidth: this.linewidth,
                            states: {
                                hover: {
                                    enabled: false,
                                    radius: 3
                                }
                            },
                            shadow: this.shadow
                        }
                    },
                    names : this.tags,
                    colors : (this.colors),
                    series: this.startSeries(ev)
                }); 
                
                this.element.chart = this.chart;
                this.addBound();
                if (this.complete)
                    this.complete();
            }
            else {
                this.addSeries(ev);
                      
            }

        }
    }
}

libutil.trendchart.prototype.setcolor = function(id, color){
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        this.chart.get(this.elid+'___'+id).color=color;
    }
}

libutil.trendchart.prototype.removeseries = function(id){
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        this.chart.get(this.elid+'___'+id).remove();
    }
}

libutil.trendchart.prototype.getExtremes = function(id){
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        return this.chart.get(this.elid+'___'+id).yAxis.getExtremes();
    }
}

libutil.trendchart.prototype.setExtremes = function(id, min, max){
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        this.chart.get(this.elid+'___'+id).yAxis.setExtremes(min,max);
    }
}

libutil.trendchart.prototype.setExtremesAuto = function(id){
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        var yax = this.chart.get(this.elid+'___'+id).yAxis;
        var ext =yax.getExtremes();
        if (ext)
            yax.setExtremes(ext.dataMin,ext.dataMax);          
    }
}

libutil.trendchart.prototype.setSelect = function(id){
    if (this.chart && this.selectedseries && this.chart.get(this.selectedseries+'___'+id)){
        this.chart.get(this.selectedseries+'___'+id).select(false);
    } 
    this.selectedseries=undefined;
    if (this.chart && this.chart.get(this.elid+'___'+id)){
        this.selectedseries=id;
        this.chart.get(this.elid+'___'+id).select(true);
    }
}

/////////////////////////////////////////////////

libutil.dom.clearChildNode = function (element){
    if (element){
        while (element.hasChildNodes()) 
            element.removeChild(element.lastChild);
    }
}



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
                duplicate.setAttribute(el.attributes[i].localName, el.attributes[i].value);
        } 
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


libutil.dom.writeDoc = function (doc, postfix){
    if (doc && window.$$writefile){
        var xmls = new XMLSerializer();  
        var data= xmls.serializeToString(doc); 
        $$writefile(postfix ?  libutil.regex.add_postfix_file(doc.baseURI,postfix) : doc.baseURI,data);
    }
}
      


// Throbber constructor
libutil.proggress.throbber = function(container) {
    this.parent = container;
    var size = container.width.baseVal.value < container.height.baseVal.value ? container.width.baseVal.value : container.height.baseVal.value;
    var cx = container.width.baseVal.value / 2;
    var cy = container.height.baseVal.value / 2;
    var sizeR = size * libutil.proggress.throbber.RELATIVE_SIZE ;
    var x = cx - sizeR / 2;
    var y = cy - sizeR / 2;
    this.trob = libutil.svg.create_element( 'image', this.parent,   [{
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
    this.trob.setAttributeNS(libutil.XLINK_NAMESPACE_URL, 'xlink:href', '../util/css/res/throbber.svg' );
    return this;
};


libutil.proggress.throbber.RELATIVE_SIZE = 0.3;


libutil.proggress.throbber.prototype.destroy = function(){
    if (this.parent && this.trob)
        this.parent.removeChild(this.trob);
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



// database

libutil.database = {};

libutil.database.APPINFOFILE = 'AppMetaInfo.xml';

libutil.database.ERROR_NO_APPINFO = "Нет файла описания ";

libutil.database.ERROR_WR_APPINFO = "Неверный формат ";

libutil.database.ERROR_WR_APPTRINFO = "Несовпадение таблицы индексов и описания ";

libutil.database.MESSAGE_CONNECTING = "Установка соединения";

libutil.database.MESSAGE_DATAREQUEST = "Запрос данных";

libutil.database.FATAL = 2;

libutil.database.RETRY = 1;

libutil.database.PROCCESS = 0;


libutil.database.getXMLData = function(obj, root){
    
    var doc = libutil.dom.readDoc(libutil.database.APPINFOFILE); 
    
    if (!doc) throw libutil.database.ERROR_NO_APPINFO  + libutil.database.APPINFOFILE;
             
    
    var rootel = doc.getElementsByTagName('meta');
    
    if (!rootel || !rootel.length) throw (libutil.database.ERROR_WR_APPINFO + libutil.database.APPINFOFILE);
    
    rootel=rootel[0];
    
    obj.connectionstring = rootel.getAttribute("constring");
    
    obj.provider = rootel.getAttribute("DBProvider").valueOf();

    if (!obj.connectionstring || !obj.provider) throw (libutil.database.ERROR_WR_APPINFO  + libutil.database.APPINFOFILE);
               
    var els = doc.getElementsByTagName(root);
    
    if (!els || !els.length) throw (libutil.database.ERROR_WR_APPINFO  + libutil.database.APPINFOFILE);
    
    return els[0];
                  
};

libutil.database.reportError = function(ev, obj, noinit){
        switch(ev.error){
            case 2049: {
                var ts = obj;
                libutil.database.modal(libutil.database.RETRY, ev.what, function(){
                    libutil.database.clearmodal();
                    ts.connect(noinit)
                });
                break;
            }
            default: {
                libutil.database.modal(libutil.database.FATAL, ev.what);    
            }
        }
        return;
}

libutil.database.modal = function(state, message, call){
    libutil.database.clearmodal();
    switch(state){
        case libutil.database.FATAL:{
            if (document.getElementById('alerttext')) document.getElementById('alerttext').textContent=message ? message: ''; 
            $('#runmodalalert').dialog({
                modal: true, 
                resizable: false,
                closeOnEscape: false, 
                disabled: true, 
                title: "Фатальная ошибка", 
                dialogClass: "alert",  
                buttons: {
                    "Выход": function() {
                        document.close();
                    }
                }
            });
            break;
        }
        case libutil.database.RETRY:{
    
            if (document.getElementById('alerttext')) document.getElementById('alerttext').textContent=message ? message: ''; 
            $('#runmodalalert').dialog({
                modal: true, 
                resizable: false, 
                closeOnEscape: false, 
                disabled: true, 
                title: "Oшибка", 
                dialogClass: "alert",  
                buttons: {
                    "Выход": function() {
                        document.close();
                    }, 
                    "Повторить" :  call
                }
            });
            break;
        }
        default:{
            $('#runmodal').dialog({
                modal: true, 
                resizable: false, 
                closeOnEscape: false, 
                disabled: true, 
                title: message
            });     
        }    
    }
}

libutil.database.clearmodal = function(){
    $('#runmodal').dialog('close');
    $('#runmodalalert').dialog('close');
    $('#runmodal').dialog('destroy');
    $('#runmodalalert').dialog('destroy');
}

libutil.database.datepickerset = function(){
    $.datepicker.regional['ru'] = {
        closeText: 'Закрыть',
        prevText: '<Пред',
        nextText: 'След>',
        currentText: 'Сегодня',
        monthNames: ['Январь','Февраль','Март','Апрель','Май','Июнь',
        'Июль','Август','Сентябрь','Октябрь','Ноябрь','Декабрь'],
        monthNamesShort: ['Янв','Фев','Мар','Апр','Май','Июн',
        'Июл','Авг','Сен','Окт','Ноя','Дек'],
        dayNames: ['воскресенье','понедельник','вторник','среда','четверг','пятница','суббота'],
        dayNamesShort: ['вск','пнд','втр','срд','чтв','птн','сбт'],
        dayNamesMin: ['Вс','Пн','Вт','Ср','Чт','Пт','Сб'],
        weekHeader: 'Не',
        dateFormat: 'dd.mm.yy',
        firstDay: 1,
        isRTL: false,
        showMonthAfterYear: false,
        yearSuffix: ''
    };
                
    $.datepicker.setDefaults($.datepicker.regional['ru']);

          
    $.timepicker.regional['ru'] = {
        timeOnlyTitle: 'Выберите время',
        timeText: 'Время',
        hourText: 'Часы',
        minuteText: 'Минуты',
        secondText: 'Секунды',
        millisecText: 'миллисекунды',
        currentText: 'Сейчас',
        closeText: 'Закрыть',
        ampm: false
    };
    $.timepicker.setDefaults($.timepicker.regional['ru']);
}

libutil.database.date = function(date){
    var d = date.getDate();
    var m = date.getMonth()+1;
    var y = date.getFullYear();
    return '' + y +'-'+ (m<=9?'0'+m:m) +'-'+ (d<=9?'0'+d:d) + '  ' + date.toLocaleTimeString();
}

// trend_controller
  
libutil.trend_controller = function(){
    try{

        this.items = [];
        this.range={};
        this.datarange={};
        this.base={};        
        this.pugerange= function(){
            var tmp={};
            for(var key in this.range) {
                if (this.range[key])
                    tmp[key]=this.range[key];
                    
            }
            this.range=tmp;
            var datatmp={};
            for(var key in this.datarange) {
                if (this.datarange[key])
                    datatmp[key]=this.datarange[key];
                    
            }
            this.datarange=datatmp;
        }
        this.xmllist = libutil.database.getXMLData(this, 'TrendList');
        this.connect();
    }
    catch(error){      
        libutil.database.modal(libutil.database.FATAL, error);
    }  
};


libutil.trend_controller.MAX_PERIOD = 360000000;

libutil.trend_controller.MIN_PERIOD = 60000;

libutil.trend_controller.MID_PERIOD = 10800000;

libutil.trend_controller.COLORS = [
    '4572A7', 
    'AA4643', 
    '89A54E', 
    '80699B', 
    '3D96AE', 
    'DB843D', 
    '92A8CD', 
    'A47D7C', 
    'B5CA92'
    ];


libutil.trend_controller.prototype.connect = function(noinit){
    try{
        var ts = this;
        this.xml= [];
        var ts = this;
        this.xml= []; 
        this.base = {};
        this.items=[];
        this.connection = undefined;            
        if (!noinit){ 
            this.init();}
        else{
            this.updateselect();
            this.updatelist();
            this.setselectpanel(false);}
        //this.setStart(new Date('Sep 10 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        this.setStart(new Date((new Date()).valueOf() - libutil.trend_controller.MID_PERIOD));
        this.setStop(new Date());        
        this.updatedate();       
        window.$$connectSCDB( 
            function(){
                var evnt= event;
                setTimeout( function(){
                    ts.attach(evnt);
                },0)
            },
            ts.provider, ts.connectionstring);
        libutil.database.modal(libutil.database.PROCCESS, libutil.database.MESSAGE_CONNECTING);
    }
    catch(error){      
        libutil.database.modal(libutil.database.FATAL, error);
    }  
};


libutil.trend_controller.prototype.attach = function(ev){
    if (ev.error){
        libutil.database.reportError(ev, this);
        return;
    }
    window.trendcontroller = this;
    this.connection = ev.connection;
    this.inittags(ev.tags);
    this.parseXMLData();
    if (!this.xml.length){
        libutil.database.modal(libutil.database.FATAL, libutil.database.ERROR_WR_APPTRINFO  + libutil.database.APPINFOFILE);
        return;
    }
    this.updatelist();

    this.requested=false;
    this.setstate(); 
    libutil.database.clearmodal();
    
}





libutil.trend_controller.prototype.parseXMLData = function(){
    this.xml=[];
    var j=0;
    for(var e=this.xmllist.firstElementChild; e; e=e.nextElementSibling){
        var lst= e.getAttribute("name");                       
        for(var el=e.firstElementChild; el; el=el.nextElementSibling){
            var arr= el.getAttribute("name"); 
            for(var et=el.firstElementChild; et; et=et.nextElementSibling){                               
                var tg = et.getAttribute("tg");
                if (this.base[tg])
                    this.xml.push({
                        list: lst, 
                        array: arr, 
                        tag: tg,
                        comment: this.base[tg].comment,
                        eu: this.base[tg].eu,
                        mineu: this.base[tg].mineu,
                        maxeu: this.base[tg].maxeu,
                        rowid: (++j).toString()
                    })                         
            }                                                        
        }
    }   
}



libutil.trend_controller.prototype.inittags = function(val){
    this.base = {};
    for (var i=0;i<val.length;++i){
        this.base[val[i].name] = val[i];
    }
}


libutil.trend_controller.prototype.init = function(){
    
    libutil.database.datepickerset();
                         
    $('body').layout({ 
        north__size:			32 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
        ,	
        north__spacing_open:	        0
                    
    });   
                
    $("#inner").layout({
        south__size:			200 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
    }); 
                
    var ts=this;    
    
    $( "#run-button" ).button({
        text: false,
        disabled: true,
        icons: {
            primary: "ui-icon-arrowrefresh-1-w"
        }
    }).click(function() {
        window.trendcontroller.run();
    ;
    })

    $( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.trendcontroller.resetselectpanel();
    ;
    });
    
    
    $( "#left-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-w"
        }
    }).click(function() {
        window.trendcontroller.setLeft();
    });
    
    $( "#right-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.trendcontroller.setRight();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.trendcontroller.setNow();
    ;
    });  
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.trendcontroller.setNow();
    ;
    });     


    $("#select-panel-trend" ).position({
        of: $( "#top-menuemain" ),
        my: 'center bottom',
        at: 'center top'
    });    
    
    this.setselectpanel(false);
    
    var panelheight = $("#select-panel-trend" )[0].getClientRects ? $("#select-panel-trend" )[0].getClientRects()[0].height : undefined;
    var bottomheight = $("#select-table-bottom" )[0].getClientRects ? $("#select-table-bottom" )[0].getClientRects()[0].height : undefined;
    
    this.startpicker = $('#starttime').datetimepicker({
        onClose:  function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStart(dt);
        }
    }).click(function(){ts.setselectpanel(false);});
    this.stoppicker = $('#stoptime').datetimepicker({
        onClose: function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStop(dt);
        }
    }).click(function(){ts.setselectpanel(false);});;  
    
    
    this.listgrid = $("#list").jqGrid({
        data: this.xml,
        autowidth: true,
        datatype: "local",
        height: panelheight ? panelheight : 'auto',
        scrollrows: true,
        shrinkToFit: true,
        cellLayout: 1,
        colNames:['list','array', 'Тег', 'Наименование', 'Ед. изм.', 'min', 'max'],
        onSelectRow: function (rowId, status, e) {
            var row = $("#list").jqGrid('getRowData',rowId);
            if (status) {
                ts.add(row.tag); 
            }
            else
            {
                ts.remove(row.tag, rowId); 
            }
          
        },
        colModel:[
        {
            name:'list',
            index:'list',  
            width:1, 
            hidden: true
        },
        {
            name:'array',
            index:'array', 
            width:1, 
            hidden: true
        },

        {
            name:'tag',
            index:'tag'
        },
        
        {
            name:'comment',
            index:'comment',
            width: 600
        },
        
        {
            name:'eu',
            index:'eu'
        },   
            
        
        {
            name:'mineu',
            index:'mineu'
        },
        
        {
            name:'maxeu',
            index:'maxeu'
        },        
    
		
        ],
   	hidegrid: false,
        viewrecords: true,
        multiselect: true,
        grouping:true,
        groupingView : {
            groupField : ['list','array'],
            groupSummary : [false],
            groupColumnShow : [false],
            groupText : ['<b>{0}</b>'],
            groupCollapse : true,
            groupOrder: ['asc'],
            groupCollapse: true
        },
        
        caption: 'Выбор параметра'
   	
    });
    

    
    
    $("#selectlist").jqGrid({
        data: this.items,
        autowidth: true,
        datatype: "local",
        height: bottomheight ? bottomheight : 'auto',
        scrollrows: true,
        shrinkToFit: false,
        cellLayout: 1,
        colNames:['Тэг', 'Наименование', 'Ед. изм.', 'Диапозон' ,'Диапозон данных' ,'Выбранный диапозон' , 'Авто', 'Выбор' ,'Цвет' , ' ', 'color', 'auto', 'min', 'max', 'mineu', 'maxeu'],
        colModel:[
                    
        {
            name:'id',
            index:'id'
        },
        
        {
            name:'comment',
            index:'comment',
            width: 600
        },
        
        {
            name:'eu',
            index:'eu'
        },  
        {
            name:'range',
            index:'range'
        },  
        {
            name:'datarange',
            index:'datarange'
        },    
        {
            name:'selectrange',
            index:'selectrange'
        },          
        {
            name:'autoedit',
            index:'autoedit',
            width:30
        },
        {
            name:'rangeedit',
            index:'rengeedit',
            width:260
        },        
        {
            name:'coloredit',
            index:'coloredit'

        }, 
  
        {
            name: 'oprt', 
            width:35, 
            fixed:true
        },

        {
            name:'color',
            index:'color',
            width: 1

        },  
        {
            name:'auto',
            index:'auto',
            width: 1

        },  
        {
            name:'min',
            index:'min',
            width: 1

        },          
        {
            name:'max',
            index:'max',
            width: 1

        },  	
        {
            name:'mineu',
            index:'mineu',
            width: 1            
        },
        
        {
            name:'maxeu',
            index:'maxeu',
            width: 1            
        }	
        ],
   	
        viewrecords: false,
        onSelectRow: function (rowId, status, e) {
            var row = $("#selectlist").jqGrid('getRowData',rowId);
            ts.setselect(row.id, status);         
        },        
        gridComplete: function(){ 
            var ids = $("#selectlist").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
               
                var row = $("#selectlist").jqGrid('getRowData',ids[i]);
                var colid = 'selectlist_selectcolor_'+ids[i];
                var rangeid = 'selectlist_selectrange_'+ids[i];
                var delid = 'selectlist_selectremove_'+ids[i];
                var autostate= row.auto=="true" ? 'checked="true"' : '';
               
                var col =   "<input  class='color-selector-ui' style='background-color:#"+ row.color + "' type='text'  value='"+ row.color + "'  id='"+colid+"'/>";
                var aut =   "<input  style='' type='checkbox' " + autostate + "  onchange=\"window.trendcontroller.setauto('"+row.id+"',this.checked)\"/>";
                var range = "<div id='"+rangeid+"' style='padding-left: 10px, padding-right: 10px; width: 100%;'/>";
                var del =   "<button id='"+delid+"' style='height: 18px' onclick=\"window.trendcontroller.remove('"+row.id+"')\">Удалить</button>";
               
                $("#selectlist").jqGrid('setCell',ids[i] ,'coloredit' ,col);
                $("#selectlist").jqGrid('setCell',ids[i] ,'autoedit' ,aut);
                $("#selectlist").jqGrid('setCell',ids[i] ,'oprt' ,del);
   
               
                $('#'+colid)[0].nameid=row.id;              
                $('#'+colid).colorpicker({
                    close: function(ev,col){
                        ev.target.setAttribute('style','background-color:#'+col.formatted);
                        ts.setcolor(ev.target.nameid, col.formatted);
                    },
                    select: function(ev,col){
                        ev.target.setAttribute('style','background-color:#'+col.formatted);
                    }                   
                });                             
                if (row.auto!="true"){
                    $("#selectlist").jqGrid('setCell',ids[i] ,'rangeedit' ,range);
                    $('#'+rangeid)[0].nameid=row.id;
                    $('#'+rangeid).slider({
                        range: true,
                        min: parseFloat(row.mineu),
                        max: parseFloat(row.maxeu),
                        values: window.trendcontroller.range[row.id] ? [ window.trendcontroller.range[row.id].min , window.trendcontroller.range[row.id].max ] : [ row.min.valueOf(), row.max.valueOf() ],
                        change: function(ev, ui) {
                            window.trendcontroller.setextremes(ev.target.nameid, ui.values[ 0 ],ui.values[ 1 ])
                        }
                    });
                }           
                $('#'+delid).button({
                    text: false,
                    icons: {
                        primary: "ui-icon-circle-minus"
                    }
                });
            }
        }         
        	
    });                               
}; 



   


libutil.trend_controller.prototype.add = function(tag){
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==tag)
            return false;
    }
    if (this.base[tag]){
        this.items.push({
            oprt : '',            
            id : tag, 
            comment : this.base[tag].comment, 
            eu : this.base[tag].eu,  
            mineu : this.base[tag].mineu,  
            maxeu : this.base[tag].maxeu,
            color: this.selectcolor(),
            coloredit: '',
            auto: true,
            autoedit: '',
            rangeedit: '',
            min: this.base[tag].mineu,
            max: this.base[tag].max,
            range: (this.base[tag].mineu + ' - ' + this.base[tag].maxeu),
            selectrange: '',
            datarange: ''
        });
        this.updateselect();                
        return true;
    }
    return false;    
}


libutil.trend_controller.prototype.remove= function(id, exclude){
    var fnd = null;
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            fnd=i;
            break;
        }
    }
    if (fnd===null) return false;         
    var ids = $("#list").jqGrid('getDataIDs');
    for(var i=0;i < ids.length;i++){
        var row = $("#list").jqGrid('getRowData',ids[i]);
        if (row && row.tag==id && (ids[i]!=exclude)) {
            $("#list").jqGrid('setSelection',ids[i],false);
        }
    }
    libutil.util.remove_element_arr(this.items,fnd);
    this.range[id] = undefined;
    this.datarange[id] = undefined;    
    if(this.trendchart)
        this.trendchart.removeseries(id);
    this.updateselect();
    this.pugerange();
    return true;      
}

libutil.trend_controller.prototype.selectcolor = function(){
    var result = 'FF0000';
    var j=0;
    while (j<libutil.trend_controller.COLORS.length){
        var fnd = false;
        for (var i=0;i<this.items.length;++i){
            if (this.items[i].color==libutil.trend_controller.COLORS[j])
                fnd = true;
        }
        if (!fnd) return libutil.trend_controller.COLORS[j];
        j++;
    }
    return result;
}


libutil.trend_controller.prototype.updatedataextremes = function(){
    for (var i=0;i<this.items.length;++i){
        var id = this.items[i].id;
        var ext=this.trendchart ? this.trendchart.getExtremes(id) : null;
        this.datarange[id] = ext ? {
            min : ext.dataMin,
            max : ext.dataMax
        } : undefined;
                   
        this.items[i].datarange= ext && (ext.dataMax || ext.dataMax===0) && (ext.dataMin || ext.dataMin===0) ? 
        (ext.dataMin.toFixed(2)  + ' - ' + ext.dataMax.toFixed(2)) : '';                                         
    }  
    this.updateselect(); 
}

libutil.trend_controller.prototype.updateselect = function( req ) {
    $("#selectlist").jqGrid('clearGridData');
    for (var i=0;i<this.items.length;++i)
        this.items[i].rowid=(i+1).toString();
    //    $("#selectlist").jqGrid('addRowData',(i+1).toString(),this.items[i]);    
    $("#selectlist").jqGrid('addRowData','rowid',this.items); 
    this.requested=req;
    this.setstate();
}

libutil.trend_controller.prototype.updatelist = function( req ) {
    $("#list").jqGrid('clearGridData');
    //for (var i=0;i<this.xml.length;++i)
    //    this.xml[i].rowid=(i+1).toString();
    //    $("#list").jqGrid('addRowData',(i+1).toString(),this.xml[i]); 
        $("#list").jqGrid('addRowData',"rowid",this.xml);   
        $("#list").trigger("reloadGrid");
}


    
libutil.trend_controller.prototype.tags = function(){
    var rslt = [];
    for (var i=0;i<this.items.length;++i)
        rslt.push(this.items[i].id);   
    return rslt;
}  

libutil.trend_controller.prototype.colors = function(){
    var rslt = [];
    for (var i=0;i<this.items.length;++i)
        rslt.push('#'+this.items[i].color);   
    return rslt;
} 

libutil.trend_controller.prototype.run = function(){
    this.setselectpanel(false);
    libutil.database.modal(libutil.database.PROCCESS, libutil.database.MESSAGE_DATAREQUEST );
    if (this.trendchart)
        this.trendchart.detach();
    var ts = this;
    ts.requested=true;
    ts.setstate();
    this.trendchart = new libutil.trendchart( 
    {
        connection: this.connection , 
        tags: this.tags(), 
        element: "chart-id", 
        colors: this.colors(),  
        start: this.start , 
        stop: this.stop, 
        ranges: this.range,
        callback: function(ev){
            if (ev.error) {
                  libutil.database.reportError(ev, ts, true);
                  return;
            }
            else{
            $('#runmodal').dialog('close');
            ts.requested=true;
            ts.setstate();}
        },
        complete: function(){
            ts.updatedataextremes();
        }
    });
        
}


libutil.trend_controller.prototype.setStart = function(val){
    if (this.start != val){
        if (this.stop  && this.start){
            var period = (this.stop.valueOf()-this.start.valueOf());
            var potperiod = (this.stop.valueOf()-val.valueOf());
            if (potperiod>libutil.trend_controller.MIN_PERIOD){
                if (potperiod>libutil.trend_controller.MAX_PERIOD)
                    this.stop=new Date(val.valueOf() + libutil.trend_controller.MAX_PERIOD);  
                this.start=val;
            }
            else{
                this.start=val;
                this.stop = new Date(val.valueOf() + libutil.trend_controller.MIN_PERIOD);
            }         
            this.normalizePeriod();
        }
        else{
            this.start=val;
            this.normalizePeriod();
        }
    }
}

libutil.trend_controller.prototype.setStop = function(val){
    if (this.stop!= val){
        if (this.stop  && this.start){
            var period = (this.stop.valueOf()-this.start.valueOf());
            var potperiod = (val.valueOf()-this.start.valueOf());
            if (potperiod>libutil.trend_controller.MIN_PERIOD){
                if (potperiod>libutil.trend_controller.MAX_PERIOD)
                    this.start=new Date(val.valueOf() - libutil.trend_controller.MAX_PERIOD);  
                this.stop=val;
            }
            else{
                this.stop=val;
                this.start = new Date(val.valueOf() - libutil.trend_controller.MID_PERIOD);
            }         
            this.normalizePeriod();
        }
        else{
            this.stop=val;
            this.normalizePeriod();
        }
    }
}

libutil.trend_controller.prototype.setLeft = function(){
    var period = (this.stop.valueOf()-this.start.valueOf());
    this.start=new Date(this.start.valueOf() - period);
    this.stop=new Date(this.stop.valueOf() - period); 
    this.normalizePeriod();
    this.run();
}

libutil.trend_controller.prototype.setRight = function(){
    var period = (this.stop.valueOf()-this.start.valueOf());
    if ((new Date()).valueOf()<this.stop.valueOf()) {
       this.start=new Date((new Date()).valueOf() - period);
       this.stop=new Date(this.start.valueOf() + period);         
    }
    else{
       this.start=new Date(this.start.valueOf() + period);
       this.stop=new Date(this.stop.valueOf() + period);        
    }
    this.normalizePeriod();
    this.run();
}

libutil.trend_controller.prototype.setNow = function(){
    var period = (this.stop.valueOf()-this.start.valueOf());
    this.start=new Date((new Date()).valueOf() - period);
    this.stop=new Date(this.start.valueOf() + period);         
   
    this.normalizePeriod();
    this.run();
}

libutil.trend_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

libutil.trend_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}

libutil.trend_controller.prototype.setcolor = function(id, col){
    
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if(this.trendchart)
                this.trendchart.setcolor(id,'#'+col);
            this.items[i].color=col;
            this.requested=false;
            this.setstate();
            break;
        } 
    }
}
libutil.trend_controller.prototype.setselect = function(id, state){
       if(this.trendchart)
            this.trendchart.setSelect(id, state);
}

libutil.trend_controller.prototype.setauto = function(id, val){
    
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if (this.items[i].auto!=val){
                if (!val){
                    var ext=this.trendchart ? this.trendchart.getExtremes(id) : null;
                    this.range[id] = {
                        min : (ext ? ext.min : this.items[i].mineu),
                        max : (ext ? ext.max : this.items[i].maxeu)
                    };
                    this.items[i].selectrange= ext ? (this.range[id].min + ' - ' + this.range[id].max) : '';
                }          
                else{
                    this.range[id] = undefined; 
                    this.items[i].selectrange= '';
                    if (this.trendchart) 
                        this.trendchart.setExtremesAuto(id);
                }           
                this.items[i].auto=val;
                this.updateselect();
                this.pugerange();
                break;
            }
        } 
    }
}

libutil.trend_controller.prototype.setextremes = function(id, min, max){
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if(this.trendchart){
                this.trendchart.setExtremes(id, min, max);
                this.range[id] = {
                    min : min,
                    max : max
                };
                this.items[i].selectrange=(min + ' - ' + max); 
                this.updateselect();
            }   
        }
    }
}



libutil.trend_controller.prototype.setselectpanel = function(val){
    var panel = $( "#select-panel-trend" )[0];
    panel.className = val ? 'ui-widget-content select-panel-visible' : 'ui-widget-content select-panel-hidden';
    panel.visibility = val ? true : false;   
}

libutil.trend_controller.prototype.resetselectpanel = function(){
    var panel = $( "#select-panel-trend" )[0];
    this.setselectpanel(!panel.visibility);    
}


libutil.trend_controller.prototype.setstate = function(){
    $( "#run-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#left-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#right-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");    
    $( "#select-button" ).button((this.xml.length) ? "enable"  : "disable");
    $( "#print-button" ).button((this.trendchart) ? "enable"  : "disable");
    if (!this.items.length && this.xml.length)
        this.setselectpanel(true);
}


// journal_controller


  
libutil.journal_controller = function(){
    try{

        this.items = [];
        this.datarange={};
        this.base={};        
        this.xmllist = libutil.database.getXMLData(this, 'meta');
        this.connect();
    }
    catch(error){      
        libutil.database.modal(libutil.database.FATAL, error);
    }  
};


libutil.journal_controller.MAX_PERIOD = 2678400000;

libutil.journal_controller.MIN_PERIOD = 60000;

libutil.journal_controller.HOUR_PERIOD = 3600000;

libutil.journal_controller.DAY_PERIOD = 86400000;


libutil.journal_controller.prototype.connect = function(){
    try{
        var ts = this;
        this.xml= [];
        this.journal= [];
        this.init();
        this.setStart(new Date('Sep 01 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        //this.setStart(new Date((new Date()).valueOf() - libutil.journal_controller.DAY_PERIOD));
        this.setStop(new Date());        
        this.updatedate();       
        window.$$connectSCDB( 
            function(){
                var evnt= event;
                setTimeout( function(){
                    ts.attach(evnt);
                },0)
            },
            ts.provider, ts.connectionstring);
        libutil.database.modal(libutil.database.PROCCESS, libutil.database.MESSAGE_CONNECTING);
    }
    catch(error){      
        libutil.database.modal(libutil.database.FATAL, error);
    }  
};

libutil.journal_controller.prototype.init = function(){
    
 
    libutil.database.datepickerset();            
          
    $('body').layout({ 
        north__size:			32 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
        ,	
        north__spacing_open:	        0
                    
    });   
                
    $("#inner").layout({
        south__size:			200 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
    }); 
                
    var ts=this;    
    
    $( "#run-button" ).button({
        text: false,
        disabled: true,
        icons: {
            primary: "ui-icon-arrowrefresh-1-w"
        }
    }).click(function() {
        window.journalcontroller.run();
    ;
    })

    /*$( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.trendcontroller.resetselectpanel();
    ;
    });*/
    
    
    $( "#day-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowstop-1-e"
        }
    }).click(function() {
        window.journalcontroller.setLastDay();
    });
    
    $( "#hour-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.journalcontroller.setLastHour();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.journalcontroller.setNow();
    ;
    });  
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.trendcontroller.setNow();
    ;
    });     

    this.startpicker = $('#starttime').datetimepicker({
        onClose:  function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStart(dt);
        }
    }).click(function(){});
    this.stoppicker = $('#stoptime').datetimepicker({
        onClose: function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStop(dt);
        }
    }).click(function(){});
    
    var tableheight = $("#inner" )[0].getClientRects ? $("#inner" )[0].getClientRects()[0].height : undefined;
    
    
    this.tabgrid = $("#table-id").jqGrid({
        data: this.journal,
        autowidth: true,
        datatype: "local",
        height: tableheight ? tableheight : 'auto',
        scrollrows: true,
        shrinkToFit: true,
        sortable: false,

        colNames:[' ', 'Тег', 'Время', 'Сообщение', 'Группа','Значение','User', 'level', 'Type'],
        gridComplete: function(){ 
            var ids = $("#table-id").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
                var imgid = 'table_id_img_'+ids[i];
                var col =   "<span   class='message-message-icon' id='"+imgid+"'></span>";
                var row = $("#table-id").jqGrid('getRowData',ids[i]);
                $("#table-id").jqGrid('setCell',ids[i] ,'icon' ,col);
                $("#table-id").jqGrid('setRowData',ids[i],undefined,window.journalcontroller ? window.journalcontroller.getClassRow(parseInt(row.type), parseInt(row.level)): undefined);
                
            }
        },
        colModel:[  
        {
            name:'icon',
            index:'icon',
            title: false,
            width: 20,
            sortable: false
        },                    
        {
            name:'tag',
            index:'tag',
            title: false,
            sortable: false
        },
        {
            name:'time',
            index:'time',
            width: 150,
            title: false
            
        },

        {
            name:'text',
            index:'text',
            width: 600,
            title: false,
            sortable: false
        },
        {
            name:'agroup',
            index:'agroup',
            width: 100,
            title: false,
            sortable: false
        },        
        
        {
            name:'value',
            index:'value',
            title: false
            
        },
        
        {
            name:'user',
            index:'user',
            title: false,
            sortable: false
            
        },   
        {
            name:'level',
            index:'level',
            title: false,
            width: 1
        },  
    
        {
            name:'type',
            index:'type',
            title: false,
            width: 1
        },        
    
		
        ],
   	rowNum: 100000,
        viewrecords: true,
        sortable: true,
        sortname: 'time',
        sortorder: 'desc'
   	
    });


}

libutil.journal_controller.prototype.attach = function(ev){
    if (ev.error){
        libutil.database.reportError(ev, this);
        return;
    }
    window.journalcontroller = this;
    this.connection = ev.connection;
    this.requested=false;
    this.setstate(); 
    libutil.database.clearmodal();
    
}


libutil.journal_controller.prototype.run = function(){
    var ts=this;
    libutil.database.modal(libutil.database.PROCCESS, libutil.database.MESSAGE_DATAREQUEST);
    this.connection.select_journal ( function(){var evnt=event;window.journalcontroller.dataresponse(evnt);}, this.start , this.stop, this.filter());
}

libutil.journal_controller.prototype.dataresponse = function(ev){
    this.journal = ev.table;
    libutil.database.clearmodal();
    this.filltable();
}

   /* const msgtype msNew        = 0x00;
    const msgtype msKvit       = 0x01;
    const msgtype msOut        = 0x02;
    const msgtype msOn         = 0x03;
    const msgtype msOff        = 0x04;
    const msgtype msCmd        = 0x05;
    const msgtype msTimeEvent  = 0x06;
    const msgtype msTimeAlarm  = 0x07;*/

libutil.journal_controller.prototype.getClassRow = function( type,lev){
    switch(type){
        case 0:{
            //msgtype msNew        = 0x00
            switch(lev){
                case 3:
                    return 'message-accedent-new';
                case 2:
                    return 'message-alarm-new';            
                case 1:
                    return 'message-warning-new';         
            }                
            break;
        }
        case 1:{
            //msgtype msKvit       = 0x01
            switch(lev){
                case 3:
                    return 'message-accedent-kvit';
                case 2:
                    return 'message-alarm-kvit';            
                case 1:
                    return 'message-warning-rvit';         
            }                
            break;
        }        
        case 2:{
            //msgtype msOut       = 0x02
            switch(lev){
                case 3:
                    return 'message-accedent-out';
                case 2:
                    return 'message-alarm-out';            
                case 1:
                    return 'message-warning-out';         
            }                
            break;
                
         }
        case 3:{
            //msgtype msOn       = 0x03                
            return 'message-message-on';             
            break;                
         }
        case 4:{
            //msgtype msOn       = 0x04                
            return 'message-message-off';             
            break;                
         }  
        case 5:{
            //msgtype msCommand       = 0x05                
            return 'message-message-command';             
            break;                
         }          
        case 5:{
            //msgtype msCommand       = 0x05                
            return 'message-message-event';             
            break;                
         }} 
    return '';
}

libutil.journal_controller.prototype.filltable = function() {
    $("#table-id").jqGrid('clearGridData');
    for (var j=0;j<this.journal.length;++j){
        var i=j;//this.journal.length-1-j;
        this.journal[i].time= libutil.database.date(this.journal[i].time);
        this.journal[i].icon= '';
        this.journal[i].rowid=(i+1).toString();} 
         $("#table-id").jqGrid('addRowData',"rowid" ,this.journal);
         $("#table-id").trigger("reloadGrid");
    this.requested=false;
    this.setstate();
}

libutil.journal_controller.prototype.filter = function(){
   
    return undefined;
}

libutil.journal_controller.prototype.setStart = function(val){
    if (this.start != val){
        if (this.stop  && this.start){
            var period = (this.stop.valueOf()-this.start.valueOf());
            var potperiod = (this.stop.valueOf()-val.valueOf());
            if (potperiod>libutil.journal_controller.MIN_PERIOD){
                if (potperiod>libutil.journal_controller.MAX_PERIOD)
                    this.stop=new Date(val.valueOf() + libutil.journal_controller.MAX_PERIOD);  
                this.start=val;
            }
            else{
                this.start=val;
                this.stop = new Date(val.valueOf() + libutil.journal_controller.MIN_PERIOD);
            }         
            this.normalizePeriod();
        }
        else{
            this.start=val;
            this.normalizePeriod();
        }
    }
}

libutil.journal_controller.prototype.setStop = function(val){
    if (this.stop!= val){
        if (this.stop  && this.start){
            var period = (this.stop.valueOf()-this.start.valueOf());
            var potperiod = (val.valueOf()-this.start.valueOf());
            if (potperiod>libutil.journal_controller.MIN_PERIOD){
                if (potperiod>libutil.journal_controller.MAX_PERIOD)
                    this.start=new Date(val.valueOf() - libutil.journal_controller.MAX_PERIOD);  
                this.stop=val;
            }
            else{
                this.stop=val;
                this.start = new Date(val.valueOf() - libutil.journal_controller.MIN_PERIOD);
            }         
            this.normalizePeriod();
        }
        else{
            this.stop=val;
            this.normalizePeriod();
        }
    }
}


libutil.journal_controller.prototype.setLastHour = function(){
    var period = libutil.journal_controller.HOUR_PERIOD;
    this.start=new Date((new Date()).valueOf() - period);
    this.stop=new Date(this.start.valueOf() + period);         
    this.normalizePeriod();
    this.run();
}

libutil.journal_controller.prototype.setLastDay = function(){
    var period = libutil.journal_controller.DAY_PERIOD;
    this.start=new Date((new Date()).valueOf() - period);
    this.stop=new Date(this.start.valueOf() + period);         
    this.normalizePeriod();
    this.run();
}

libutil.journal_controller.prototype.setNow = function(){
    var period = (this.stop.valueOf()-this.start.valueOf());
    this.start=new Date((new Date()).valueOf() - period);
    this.stop=new Date(this.start.valueOf() + period);         
   
    this.normalizePeriod();
    this.run();
}

libutil.journal_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

libutil.journal_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}

libutil.journal_controller.prototype.setstate = function(){
    $( "#run-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#hour-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#day-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");} 