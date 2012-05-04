var dsutl = {};

dsutl.SELECT_MODE = null;

///
dsutl.componentinfo = function(){
    this.elements = {};
    this.types = {};
    this.libs = [];
    this.creators = {};
}


dsutl.trslt = {};

dsutl.toolwin = {};
   
   
   
   

///

function designer(doc){ 
    
    this.instantdocument=doc;
    this.schema=new dsutl.componentinfo();
    this.schema.init('../util/lib.xsl');
    this.getSourseDocument();
    this.getLightDocument();
    this.instantdocument.addEventListener('keyup' ,function (ev) {
        if (document.red)
            document.red.keybordDispatcherd(ev)
    });
    this.instantdocument.addEventListener('mousemove' ,function (ev) {
        if (document.red)
            document.red.mousemoveDocument(ev)
    });
    this.instantdocument.addEventListener('mousedown' ,function (ev) {
        if (document.red)
            document.red.mousedownDocument(ev)
    });
    this.instantdocument.addEventListener('mouseup' ,function (ev) {
        if (document.red)
            document.red.mouseupDocument(ev)
    });    
    this.instantdocument.addEventListener('contextmenu' ,function (ev) {
        if (document.red)
            document.red.createContextMenu(ev);
        event.stopPropagation();
        event.preventDefault();  
    });        
    
    this.attach(this.instantdocument.documentElement);
    
    this.needsave=false;
}


// привязка ко всем элементам
designer.prototype.attach = function(el){
    try{
        if (el==this.instantdocument.documentElement){
            el.oldoncick = el.oncick;
            el.onclick = function() {
                if (document.red){
                    document.red.clearSelections();
                    document.red.clickParented(el);
                    dsutl.toolwin.setCurrentRedactor(window);
                    document.red.show_property(document.documentElement);
                }
            };
        }
        else{
            if ((el.hasAttribute)  && (el.id!="") && (el.hasAttribute('isdesined'))) {
                var parentclass = el.parentNode.getAttribute('class');
                if (parentclass!='designer_selected'){
                el.oldoncick = el.oncick;
                el.onclick= function() {
                    if (el.hasAttribute('isgoupelement')){
                        if (document.red) document.red.clickCanParented(el, event);
                    }
                    else{
                        if (document.red) document.red.clickComponent(event);
                    }}
                };

                el.addEventListener('keyup', function() {
                    if (document.red) document.red.onmos();
                 });
                
                el.oldonmouseout = el.onmouseout;
                el.onmouseout = function() {
                    if (document.red) document.red.onmos();
                };
                el.oldonmouseup = el.onmouseup;
                el.onmouseup = function() {
                    if (document.red) document.red.onmos();
                };
                el.oldonmousedown = el.onmousedown;
                el.onmouseup = function() {
                    if (document.red) document.red.onmos();
                };                
                el.oldonmouseover = el.onmouseover;
                el.onmouseover = function() {
                    if (document.red) document.red.onmos();
                };
                el.oldonmousewheel = el.onmousewheel;
                el.onmousewheel = function() {
                    if (document.red) document.red.onmos();
                };
                
                el.onmousemove = undefined;
                el.onmousedown = undefined;
                el.onmouseup = undefined;
                el.oncontextmenu  = undefined;

            }
        }        
    }
    catch(error){
        console.error('designer.prototype.attach error: ' + error);
    }
    for (var i=0;i<el.childNodes.length;i++){
        this.attach(el.childNodes[i]); 
    }
}


//  чтение документа источника
designer.prototype.getSourseDocument = function (){ 
    if (this.sourseDocument)
        return this.sourseDocument;
    try{
        this.sourseDocument = libutil.dom.readDoc(this.instantdocument.URL);
        if ((this.sourseDocument) && (this.sourseDocument.childNodes.length>1)){
            if (this.sourseDocument.childNodes[0].target=='xml-stylesheet'){
                if (this.sourseDocument.childNodes[0].data)
                    this.readXsltDocument(this.sourseDocument.childNodes[0].data);
            }
        }
    }
    catch(error){
        console.error('designer.prototype.getSourseDocument error: ' + error);
        this.sourseDocument = null;
    }
    return this.sourseDocument;
}



designer.prototype.getLightDocument = function (){ 
    try{
        this.lightDocument = libutil.dom.readDoc(this.instantdocument.URL);     
    }
    catch(error){
        console.error('designer.prototype.getLightDocument error: ' + error);
        this.lightDocument = null;
    }
    return this.lightDocument;   
}


designer.prototype.getLightElement = function (el){
    if (this.xsltProcessor && this.soursexslt) {
        if (this.lightDocument){
            var root = this.lightDocument.lastChild;
            if (root){
                while (root.firstChild)
                    root.removeChild(root.firstChild);                
                root.appendChild(el);
            }   
        }
        this.lightDocument = this.xsltProcessor.transformToDocument(this.lightDocument);
        return this.lightDocument.getElementById(el.getAttribute('id'));
    }
    return undefined;
}

//  чтение XSLT
designer.prototype.readXsltDocument = function(data){
    var urlxslt=data;
    var urlxslt=urlxslt.toString();
    var finded=urlxslt.search('type="text/xsl"');
    if (finded==-1)
        finded=urlxslt.search("href='");
    if (finded!=-1){
        urlxslt=urlxslt.substring(6,urlxslt.length);
        finded=urlxslt.search('"') ;
        if (finded!=-1){
            urlxslt=urlxslt.substring(0,finded);
            this.soursexslt = libutil.dom.readDoc(urlxslt);
            this.xsltProcessor=new XSLTProcessor();  
            this.xsltProcessor.importStylesheet(this.soursexslt); 
            this.trasformsourse = this.xsltProcessor.transformToDocument(this.sourseDocument);
            return;
        }
    } 
    this.xslturl=undefined;
}


designer.prototype.getTrasformDocument = function(){
    if (this.xsltProcessor && this.soursexslt)
        return this.trasformsourse = this.xsltProcessor.transformToDocument(this.sourseDocument);
    return undefined;
}



designer.prototype.getSourseElement = function(el){
    return el && el.id && this.sourseDocument ? 
    this.sourseDocument.getElementById(el.id) : null;
}


designer.prototype.getTransformElement = function(elid){
    if (this.trasformsourse) {
        var el=this.sourseDocument.getElementById(elid);
        if (el){
            el=el.cloneNode(true);
            return this.getLightElement(el);
        }
    }
    return null;
}


designer.prototype.getTarget = function (ev){
  
    var el = ev.target.correspondingUseElement ? ev.target.correspondingUseElement : ev.target;   
    var owndoc = el.ownerDocument;   
    while ((el!=owndoc) && (!(el.getAttribute('id') && el.hasAttribute('isdesined'))))
        el=el.parentNode;

    return ((el==owndoc)) || (!el.getAttribute('id')) ? undefined : el;
}



designer.prototype.unicalIdGenerate = function(el, doc, newstr, templt) {
    var i=0;
    var tmpl = templt  ? templt : 'name';
    var expr = new RegExp('[a-z]{1,}', 'i');
    if (el && (el.getAttribute('id')))
        tmpl=expr.exec(el.getAttribute('id'));

    if (tmpl=='') tmpl = 'name';
   
    var fid=tmpl + i;
    while ((doc.getElementById(fid)) || (newstr && newstr[fid]))
        fid=tmpl+ (++i);   
    return fid;
}

designer.prototype.unicalIdsGenerate  = function(el, newstr){
   if (!newstr) newstr={};
   var id = el.getAttribute('id');
   if (id && this.sourseDocument.getElementById(id)){
      var coneid=this.unicalIdGenerate(el, this.sourseDocument, newstr);
      newstr[coneid]=1;
      el.setAttribute('id',  coneid);}
      for (var ch=el.firstElementChild; ch; ch=ch.nextElementSibling){
          this.unicalIdsGenerate(ch, newstr);}
}



designer.prototype.getAttributeList = function(el) {
    if (el){
        return this.schema.getAttributeList(this.getSourseElement(el));
    }
    else
    {
        var result = [];
        var attrs = [];
        if (this.selectedElemens && this.selectedElemens.length>0){
            for (var j=0; j< this.selectedElemens.length; ++j){
                var attr = this.getAttributeList(this.selectedElemens[j].getElement());
                if (!attr) 
                    return null;
                attrs.push(attr);
            }
        }
        else{
            var attr = this.getAttributeList(this.instantdocument.documentElement); 
            attrs.push(attr);
        }
            
       
        if (attrs.lenght==0) 
            return null; 
        attr = attrs[0];
        for(var key in attr.attributes){
            var correct=true;
            if (attrs.length>1){
                for (var j=1; j< attrs.length; ++j){ 
                    if ((!attrs[j].attributes[key]) || (key=='id')){
                        correct=false;
                        break;
                    }
                }
            }
            
            if (correct)
                result.push(attr.attributes[key]);     
        }
    }
        
    return result;
};



designer.prototype.getAttributeValue = function(name, el){
    if (el){
        return this.getSourseElement(el) ? this.getSourseElement(el).getAttribute(name) : undefined;
    }  
    if ((!this.selectedElemens ) || (this.selectedElemens.length==0)) 
    {
        return this.getAttributeValue(name,this.instantdocument.documentElement);      
    }
    else
    {
        var sel = this.getSourseElement(this.selectedElemens[0].getElement());
        if (sel){
            var value=sel.getAttribute(name);
            value= value !=null ? value : undefined;
            if (this.selectedElemens.length>1){
                for (var j=1; j< this.selectedElemens.length; ++j){
                    var val=this.getAttributeValue(name, this.selectedElemens[j].getElement());
                    val= val !=null ? val : undefined;
                    if (value!=val)
                        return undefined;
                } 
            }
            return value!=undefined ? value : '';
        }
    }
return undefined;
}




designer.prototype.setAttributeValue = function(name, val, el){
    if (el){
        if (name=='id'){
            if (this.sourseDocument.getElementById(val))
                return;
        }
        var sel = this.getSourseElement(el);
        if ((!sel) && (!val)) return;
        sel.setAttribute( name, val);
        return;
    }
    if ((!this.selectedElemens ) || (this.selectedElemens.length==0)){
        this.setAttributeValue(name,val, this.instantdocument.documentElement, true);
        this.updateRoot();
    }
    else{
    for (var j=0; j< this.selectedElemens.length; ++j){
        this.setAttributeValue(name,val, this.selectedElemens[j].getElement(), true);
    }} 
}


designer.prototype.setProperty = function(nm, val){
    this.setAttributeValue(nm['name'],val);
    this.updateElement();
    this.setNeedSave();
    dsutl.toolwin.setMainWindowToolStatus(1);
    this.show_property();      
}    




designer.prototype.setSourseElementRect = function(x, y, width, height , el){
    if (el){
        this.setElementRect(x, y, width, height , this.getSourseElement(el));
        this.setNeedSave();
        return;
    }
    if ((this.selectedElemens ) || (this.selectedElemens.length>0)){  
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.setSourseElementRect(x, y, width, height, this.selectedElemens[j].getElement());
    }
  
}


designer.prototype.setElementRect = function(x, y, width, height , el){
    if (el){
        console.log(x + ' ' + dsutl.trslt.getXname(el));
        console.log(y + ' ' + dsutl.trslt.getYname(el));
        if (!el) return;
        if (x && dsutl.trslt.getXname(el)){
            switch(dsutl.trslt.getXname(el)){
            case 'd': {dsutl.trslt.setDXval( el, x);break;}
            case 'transform': {dsutl.trslt.setXTranslate( el, x);break;}
            default: {el.setAttribute( dsutl.trslt.getXname(el), x);}}}
        if (y && dsutl.trslt.getYname(el)){
            switch(dsutl.trslt.getYname(el)){
            case 'd': {dsutl.trslt.setDYval( el, y);break;}
            case 'transform': {dsutl.trslt.setYTranslate( el, y);break;}
            default: {el.setAttribute( dsutl.trslt.getYname(el), y);}}}
        if (width && dsutl.trslt.getWname(el))
            el.setAttribute( dsutl.trslt.getWname(el) , width);
        if (height  && dsutl.trslt.getHname(el))
            el.setAttribute( dsutl.trslt.getHname(el), height);
        return;
    } 
}





designer.prototype.updateElement = function(el){
    if (el) {
        console.log('designer.prototype.updateElement: '+el);
        var select = this.isSelection(el);
        var tel = this.getTransformElement(el.getAttribute('id'));
        var old = el.parentNode.replaceChild(tel ,el);
        this.attach(tel);
        if (select){
            this.repaceSelection(old, tel);
        }
    }
    else{
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.updateElement(this.selectedElemens[j].getElement(), true);
    }
   
}

designer.prototype.updateRoot = function(){
        var el = this.instantdocument.documentElement;
        var tel = this.sourseDocument.documentElement;
        if (tel.getAttribute('style')!=el.getAttribute('style'))
            el.setAttribute('style',tel.getAttribute('style'));
        if (tel.getAttribute('x')!=el.getAttribute('x'))
            el.setAttribute('x',tel.getAttribute('x'));
        if (tel.getAttribute('y')!=el.getAttribute('y'))
            el.setAttribute('y',tel.getAttribute('y'));
        if (tel.getAttribute('width')!=el.getAttribute('width'))
            el.setAttribute('width',tel.getAttribute('width'));
        if (tel.getAttribute('height')!=el.getAttribute('height'))
            el.setAttribute('height',tel.getAttribute('height'));
        if (tel.getAttribute('veiwBox')!=el.getAttribute('veiwBox'))
            el.setAttribute('veiwBox',tel.getAttribute('veiwBox'));    
        this.setNeedSave();        
          
}


designer.prototype.save = function(){
    if (this.sourseDocument){
        libutil.dom.writeDoc(this.sourseDocument);
        this.needsave=false;
    }  
}


designer.prototype.deleteElements = function(el){
    if (el){
        this.clearSelection(el);
        if (this.sourseDocument){
            var source = this.getSourseElement(el);
            if (source){
                el.parentNode.removeChild(el);
                source.parentNode.removeChild(source);
            }
        }
    }
    else{
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.deleteElements(this.selectedElemens[j].getElement());
       
        this.selectedElemens.length=0;
    }   
}

designer.prototype.cloneElements = function(el){
    if (el){
        if (this.sourseDocument){
            this.clearSelection(el);
            var source = this.getSourseElement(el);
            if (source){
                var el_c=source.cloneNode(true);
                var prnt = source.parentNode;
                this.unicalIdsGenerate(el_c);
                prnt.appendChild(el_c);
                this.getTrasformDocument();
                var tel = this.getTransformElement(el_c.getAttribute('id'));
                var prntel = el.parentNode;
                prntel.appendChild(tel);
                this.attach(tel);
                this.changeRect(10,10, null, null, tel);
                this.setSelection(tel);
                this.updateElement(tel);
                
            }
        }
    }
    else{
        for (var j=0; j< this.selectedElemens.length; ++j)  
            this.cloneElements(this.selectedElemens[j].getElement(), true);
 
    }   
}



designer.prototype.toFrontElements = function(el){
    if (el){
        var elprnt = el.parentNode;
        this.clearSelection(el);
        if (this.sourseDocument){
            var sel = this.getSourseElement(el);
            if (sel){
                var prnt = sel.parentNode;
                if (prnt.lastElementChild==sel)
                    return;                
                var cel=sel.cloneNode(true);
                prnt.removeChild(sel);
                prnt.appendChild(cel);
                var rem = elprnt.removeChild(el);
                elprnt.appendChild(rem);
                this.setSelection(rem);
            }
        }
    }
    else{
        
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.toFrontElements(this.selectedElemens[j].getElement());
     
        //this.clearSelections();

    }   
}

designer.prototype.toBackElements = function(el){
    if (el){
        var elprnt = el.parentNode;
        if (this.sourseDocument){
            this.clearSelection(el);
            var sel = this.getSourseElement(el);
            if (sel){
                var prnt = sel.parentNode;
                if (prnt.firstElementChild==sel)
                    return;                
                var cel=sel.cloneNode(true);
                prnt.removeChild(sel);
                prnt.insertBefore(cel, prnt.firstElementChild);
                var rem = elprnt.removeChild(el);
                elprnt.insertBefore(rem, elprnt.firstElementChild);
                this.setSelection(rem);
            }
        }
    }
    else{
        
        for (var j=0; j< this.selectedElemens.length; ++j) 
            this.toBackElements(this.selectedElemens[j].getElement());
        
        

    }   
}



designer.prototype.pastToClipBoard = function(clear){
    var tmp=$$global();
    tmp.clipboard=[];

    for (var i=0;i < this.selectedElemens.length;++i)
        if (this.selectedElemens[i].getElement()){
            var el = this.getSourseElement(this.selectedElemens[i].getElement());
            if (el)
                tmp.clipboard.push(el.cloneNode(true));
        }
    
    if (clear){
        for (var i=0;i < this.selectedElemens.length;++i)
            if (this.selectedElemens[i]){
                var prnt = this.selectedElemens[i].getElement().parentNode;
                var el = this.getSourseElement(this.selectedElemens[i].getElement());
                if (el){
                    var prnts = el.parentNode;
                    prnt.removeChild(this.selectedElemens[i].getElement());
                    prnts.removeChild(el);}
            }
       this.selectedElemens=[];     
    }
}
        
        
designer.prototype.clearToClipBoard = function(){
    var tmp=$$global();
    tmp.clipboard=null;
} 
        
designer.prototype.getClipBoard = function(){
    var tmp=$$global();
    return tmp.clipboard;
}   

designer.prototype.copyFromClipBoard = function( x , y, prnt){
    var tmp=$$global();
    //alert(x + '  --- '+ y);
    if (tmp.clipboard && tmp.clipboard.length>0)
    for (var i=0;i < tmp.clipboard.length;++i)
        if (tmp.clipboard[i]){
            x = dsutl.trslt.getXname(tmp.clipboard[i])=='d' ? 10 : x;
            y = dsutl.trslt.getYname(tmp.clipboard[i])=='d' ? 10 : y;
            this.createLibComponent(x, y, tmp.clipboard[i], prnt, tmp.clipboard.length > 1 )
        }
    
}




designer.prototype.changeRect = function(x, y, width , height, el){
    var sel = this.getSourseElement(el);
    if (sel){
        var xnmame = dsutl.trslt.getXname(sel);
        var ynmame = dsutl.trslt.getYname(sel);
        var xval = null;
        var yval = null;
        if (x && xnmame){
            switch(xnmame){
                case 'd': {xval=(parseFloat(dsutl.trslt.getDXval(sel)) + x);break;}
                case 'transform': {xval=(parseFloat(dsutl.trslt.getXTranslate(sel)) + x);break;} 
                default: {xval=(parseFloat(sel.getAttribute(xnmame)) + x);}
            }
        }
        if (y && ynmame){
            switch(ynmame){
                case 'd': {yval=(parseFloat(dsutl.trslt.getDYval(sel)) + y);break;}
                case 'transform': {yval=(parseFloat(dsutl.trslt.getYTranslate(sel)) + y);break;} 
                default: {yval=(parseFloat(sel.getAttribute(ynmame)) + y);}
            }
        }
        
        
        this.setSourseElementRect(  xval , yval ,
            (width && dsutl.trslt.getWname(sel) ? parseFloat(sel.getAttribute(dsutl.trslt.getWname(sel))) + width : width) ,
            (height && dsutl.trslt.getHname(sel)? parseFloat(sel.getAttribute(dsutl.trslt.getHname(sel))) + height : height) , el);
    }

}


    
// обработчики событий   
 
/* empty*/
designer.prototype.onmos = function (){
    event.preventDefault();
    event.stopPropagation();
} 

designer.prototype.onmosnopropogate = function (){
    event.preventDefault();
} 

designer.prototype.clickComponent = function(){
    var el= this.getTarget(event);
    dsutl.toolwin.setCurrentRedactor(window);
    this.selectComponent(el, event.shiftKey, event.ctrlKey);
    event.stopPropagation();
}

designer.prototype.clickCanParented = function(el, ev){
    if (((!this.isSelection(el))) || (!this.newLibComponent((ev.pageX - el.x.baseVal.value).toString(), (ev.pageY - el.y.baseVal.value).toString(), el)))
        if (document.red) document.red.clickComponent(ev);
    event.stopPropagation();
    return false;
}

designer.prototype.clickParented = function(){
    console.log('designer.prototype.clickParented : x' + event.pageX + 'y' + event.pageY);
    if (event && event.pageX.toString() && event.pageY.toString())
        this.newLibComponent(event.pageX.toString(), event.pageY.toString());
}

designer.prototype.newLibComponent = function(x, y , prnt){
    var created = dsutl.toolwin.getSelectedComponent();
    if (created && x && y){
        console.log('designer.prototype.newLibComponent : x' + x + 'y' + y);
        this.createLibComponent(x, y, created, prnt);
        this.show_property();
        dsutl.toolwin.clearSelectedComponent();
        return true;
    }
    return false;
}

designer.prototype.createLibComponent = function(x, y , created, prnt, chrect){
    if (created/* && x && y*/){
        this.clearSelections();
        var coneid=this.unicalIdGenerate(created , this.sourseDocument , null, created.localName);
        var sprnt = prnt ? this.getSourseElement(prnt) : this.sourseDocument.documentElement;
        prnt = prnt ? prnt : this.instantdocument.documentElement;
        var el =sprnt.appendChild(created.cloneNode(true)); 
        el.setAttribute('id',  coneid);
        this.setElementRect(x,y, null, null, el);        
        this.getTrasformDocument();        
        var tel = this.getTransformElement(coneid);
        prnt.appendChild(tel);
        this.attach(tel);
        this.setSelection(tel);
        //chrect ? this.changeRect(x,y, null, null, el) : this.setSourseElementRect(x,y, null, null, tel);
        this.updateElement(tel);
        this.setNeedSave();
        return true;
    }
    return false;
}


//  Выбор компонента на форме


designer.prototype.isSelection = function(el){
    if (el && this.selectedElemens) {
        for (var j=0; j< this.selectedElemens.length; ++j)
            if (this.selectedElemens[j].getElement()==el) return true;
    }
    return false;        
}


designer.prototype.isSelectionParent = function(el){
    if (el && this.selectedElemens) {
        for (var j=0; j< this.selectedElemens.length; ++j)
            if (this.selectedElemens[j].getElement().parentNode==el.parentNode) 
                return false;
    }
    return true;        
}

designer.prototype.selectionCount = function(){
    return this.selectedElemens && this.selectedElemens.length > 0;        
}

designer.prototype.setSelection = function(el){
    if (this.selectedElemens==null)
        this.selectedElemens = [];
    this.selectedElemens.push( new dsutl.selectwraper(el));
}

// очистка выделения элемента
designer.prototype.clearSelection = function(el){
    if (this.selectedElemens!=null)
        for (var i=0;i < this.selectedElemens.length;++i)
            if (this.selectedElemens[i].getElement()==el){
                this.selectedElemens[i].deselect();
                this.selectedElemens.splice(i,1);
                break;
            }
}

designer.prototype.repaceSelection = function(old, newel){
    this.clearSelection(old);
    this.setSelection(newel);           
}


// очистка всех выделенных элементов
designer.prototype.clearSelections = function (){
    if (this.selectedElemens!=null){
        for (var i=0;i < this.selectedElemens.length;++i){
            this.selectedElemens[i].deselect();
        };
       this.selectedElemens=[]; 
    }
    if (event)
        event.stopPropagation();
}



/*выделение элемента*/
designer.prototype.selectComponent = function(el, shift, ctnrl){
    if (this.selectedElemens==null)
        this.selectedElemens = [];
    
    //console.log('designer.prototype.selectComponent');
      
    if (this.isSelectionParent(el))
        this.clearSelections();
    
    if (!shift){
        this.clearSelections();
        this.setSelection(el);
        
    }
    else{
        if (this.isSelection(el)){
            this.clearSelection(el);
        }
        else{
            this.setSelection(el);          
        }
    }
    this.show_property();
}

designer.prototype.isNeedInsert = function (el){
    return (dsutl.toolwin.getSelectedComponent() && el.hasAttribute('isgoupelement'));
}


/*обработчик событий клавиатуры*/
designer.prototype.keybordDispatcherd = function (){
    
    this.moveElements(event);

    if ((event.keyCode==82) && (event.shiftKey)) {
        window.location.reload();
        event.stopPropagation();
        event.preventDefault();
        return;
    }

    this.show_property();
    event.stopPropagation();
}

designer.prototype.moveElements = function (event){
    
    if (!event.ctrlKey && !event.shiftKey) return;
    if (event.keyIdentifier!='Left' && event.keyIdentifier!='Right'  && event.keyIdentifier!='Down'  && event.keyIdentifier!='Up') return;
    if (!this.selectedElemens) return;
    if (this.selectedElemens.length==0) return;
    
    var incr =event.altKey ? 10 : 1;
    

    for (var i=0;i < this.selectedElemens.length;++i){
        var el=this.selectedElemens[i].getElement();
        if (event.ctrlKey) {
            switch (event.keyIdentifier){
                case 'Left':{
                    this.changeRect(-incr, null, null, null, el);
                    this.selectedElemens[i].shiftRect(-incr, null);
                    break;
                }
                case 'Right':{
                    this.changeRect( incr, null, null, null, el);
                    this.selectedElemens[i].shiftRect(incr, null);
                    break;
                }     
                case 'Up':{
                   this.changeRect(null,-incr,  null, null, el);
                   this.selectedElemens[i].shiftRect(null, -incr);
                   break;
                }
                case 'Down':{
                   this.changeRect(null,+ incr,  null, null, el);
                   this.selectedElemens[i].shiftRect(null, incr);
                   break;
                }
            }                
        }
        if (event.shiftKey){
            switch (event.keyIdentifier){        
                case 'Left':{
                    this.changeRect(null, null, - incr, null, el);
                    ismove=true;
                    break;
                }
                case 'Right':{
                    this.changeRect(null, null, + incr, null, el);
                    ismove=true;
                    break;
                }   
                case 'Up':{
                    this.changeRect(null,  null, null, - incr,  el);
                    ismove=true;
                    break;
                }
                case 'Down':{
                    this.changeRect(null,  null, null, + incr,  el);
                    ismove=true;
                    break;
                }
            }            
        }

    }
    
   
}



designer.prototype.mousemoveDocument = function (){
    if ((this.dragstartevent)){
        if (this.mousmoveevent){
            var xsh=event.pageX-this.mousmoveevent.pageX;
            var ysh=event.pageY-this.mousmoveevent.pageY;
            if (this.selectedElemens) {
                for (var i=0;i < this.selectedElemens.length;++i){
                    var el = this.selectedElemens[i].getElement();
                    this.selectedElemens[i].shiftRect(xsh, ysh);
                }}
                
        }
        if (this.inspectorFrame){
            if (this.mousmoveevent){
        }
        }
    }
    this.mousmoveevent=event;
}


designer.prototype.mousedownDocument = function (){
    if ((event.button==0) && (!event.shiftKey)){
        var trgt = this.getTarget(event)
        if (this.selectedElemens){
            if (this.selectedElemens.length>0){
                for (var i=0; i<this.selectedElemens.length;++i){ 
                    if (trgt==this.selectedElemens[i].getElement()){
                        this.dragstartevent = event;
                        return;
                    }
                }
            }
        }
    }
    this.draggedstart=undefined;
    this.dragstartevent = undefined;
    this.mousmoveevent=undefined;
}




designer.prototype.mousedownComponent = function (){
    if ((event.button==0)){
        var trgt = this.getTarget(event)
        if ((this.isSelection(trgt)) && (!designer.prototype.isNeedInsert(trgt))){
            this.draggedstart=true;
            return;
        }
    }
    this.draggedstart=undefined;
}


designer.prototype.mouseupDocument = function (){
    if (event.button==0){
        if (this.mousmoveevent){
            var xsh=event.pageX-this.mousmoveevent.pageX;
            var ysh=event.pageY-this.mousmoveevent.pageY;
            if (this.draggedstart && this.dragstartevent){               
                var sxsh=event.pageX-this.dragstartevent.pageX;
                var sysh=event.pageY-this.dragstartevent.pageY;
                //console.log('designer.prototype.mouseupDocument dx: ' + sxsh + ' dy: ' + sysh);
                if (this.selectedElemens) {
                    for (var i=0;i < this.selectedElemens.length;++i){
                        var el = this.selectedElemens[i].getElement();
                        this.changeRect( sxsh, sysh , null, null,  el);
                        this.selectedElemens[i].shiftRect(xsh, ysh);
                    }                   
                    this.setNeedSave();
                }
                this.show_property();
            }
        }
    }
    this.draggedstart=undefined;
    this.dragstartevent = undefined;
    this.mousmoveevent=undefined;

}



designer.prototype.contextmenue = function (){
    this.createContextMenu(event);
    event.stopPropagation();
    event.preventDefault();    
}




//  ****/


designer.prototype.createWindow = function(id, top, left, width, height){
   
    if (this.instantdocument){

        var style=' body { margin: 0 0; padding: 0 0; -webkit-user-select: none;}'+
        'div.scrollHeader{'+  
        'margin: 0 0; padding: 0 0; border-top-right-radius: 6px; border-top-left-radius: 6px;'+
        'border:  1px solid #000022; background: #000044; color: yellow; padding: 4px; -webkit-user-select: none;}'+  
                
        'div.scrollWrapper{'+
                
        'overflow:scroll; margin: 0 0; padding: 0 0;'+
        'border:  1px solid grey;}'+
                
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
        '}';                
            
        var result = libutil.www.create_window(this.instantdocument, id, top, left, height, width, style);
        return result;
    }
    return undefined;
}

// контекстное меню

designer.prototype.createContextMenu = function(){


    var l= event.pageX;
    var t= event.pageY;
    
    var el = event.target;
    var isRoot=(el==this.instantdocument.documentElement);
    //if (isRoot) return;

    if (!isRoot){
        el= this.getTarget(event);
        if (!el) return;
    }
    
    if (this.contextmenu)
        this.ContextMenuDestroy();

    
    this.contextmenu = this.createWindow('context_menue', l - 10 , t - 10 , 600, 200);

    var styletxt=' body { margin: 0 0; padding: 0 0; -webkit-user-select: none;}'+
    'table *{'+
    'padding: 0 0;'+
    'margin: 0 0;'+  
    'border: 0;'+
    'border-collapse: collapse;'+
    '}'+           
          
    'button {'+
    'border: 2px outset buttonface;'+
    'padding: 0 0;'+
    'margin: 0 0;'+
    'width: 100%;'+
    'outline-width: 0px;'+
                
    '}';  
        
    libutil.html.create_style(this.contextmenu.bindelement,styletxt); 
   
    var table = libutil.html.create_table(this.contextmenu.bindelement, null, 'scrollable');
    table.setAttribute('width' , '100%');
           
    var tbody= libutil.html.create_tbody(table);
       
    this.ContextMenuComponent(tbody);
    
    this.contextmenu.onmouseout=function(){
        if (event.fromElement==this) {
            document.red.ContextMenuDestroy();
        }
    }
}

designer.prototype.ContextMenuButton = function(tbody, name, enable, func){
    
    var btn = libutil.html.create_button( 
        libutil.html.create_td(
            libutil.html.create_tr(tbody)), null , null, name, func);
    if (!enable)  btn.setAttribute('disabled','disabled');      

}




designer.prototype.ContextMenuComponent = function(tbody){
    
    this.ContextMenuButton(tbody, 'Bring to Front', this.selectionCount() ,
        function(){
            document.red.toFrontElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } );
        
    this.ContextMenuButton(tbody, 'Send to Back', this.selectionCount() ,
        function(){
            document.red.toBackElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } );  
        
    this.ContextMenuButton(tbody, 'Delete', this.selectionCount(),
        function(){
            document.red.deleteElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } );  
 
    this.ContextMenuButton(tbody, 'Clone', this.selectionCount(),
        function(){
            document.red.cloneElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } ); 
        
    this.ContextMenuButton(tbody, 'Copy', this.selectionCount(),
        function(){
            document.red.pastToClipBoard();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } ); 


    this.ContextMenuButton(tbody, 'Cut', this.selectionCount(),
        function(){
            document.red.pastToClipBoard(true);
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } ); 
        
        
    this.ContextMenuButton(tbody, 'Past', this.getClipBoard(),
        function(){
            var prn=tbody.parentNode.parentNode.parentNode.parentNode.parentNode;
            document.red.copyFromClipBoard(prn ? parseFloat(prn.getAttribute('x')) : null, prn ? parseFloat(prn.getAttribute('y')) : null);
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
            event.stopPropagation();
        } );        
        
    this.ContextMenuButton(tbody, 'Close', true,
        function(){
            document.red.ContextMenuDestroy();
            event.stopPropagation();
        } );          
       
}



designer.prototype.ContextMenuDestroy = function(){
    
    if (this.contextmenu){
        this.contextmenu.parentNode.removeChild(this.contextmenu);
    }
    this.contextmenu=undefined;

}

// Инспектор объектов


designer.prototype.show_property = function(){
    
    
    var attriblist=this.getAttributeList();


    this.inspectorFrame=dsutl.toolwin.getObjectInspector();
    if (!this.inspectorFrame) return;
    this.inspectortbody=dsutl.toolwin.getObjectInspectorTbody();
    
    libutil.dom.clearChildNode(this.inspectortbody);   

    var trh= libutil.html.create_tr(this.inspectortbody);

            
    var th1= libutil.html.create_th(trh);
    th1.setAttribute('width','50%');
    th1.innerHTML='Attribute';
            
    var th2= libutil.html.create_th(trh);
    th2.setAttribute('width','50%');
    th2.innerHTML='Value';

                            
    for (var i=0; i<attriblist.length; ++i ){
        
        var tr= libutil.html.create_tr(this.inspectortbody);
       
        var td1= libutil.html.create_td(tr);
        td1.innerHTML=attriblist[i]['name'];
        
        var typenm= attriblist[i]['typename'];
        td1.className= (typenm=='lib:expression') ? 'staticexpr' : 
            ((typenm=='lib:taglist') ? 'statictaglist' :
            ((typenm=='lib:tag') ? 'statictag' :
            ((typenm=='lib:event') ? 'staticevent' :'static' )));
   
        var td2= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var val=this.getAttributeValue(attriblist[i]['name']);
        td2.innerHTML= val ? val : "";
        
        if (val==undefined)
            td2.className='diffvalue';
        
        td2.type=(!attriblist[i]['type']) ? 0 : (attriblist[i]['type']['type'] ? attriblist[i]['type']['type'] : 0) ;
        td2.regex=(!attriblist[i]['type']) ? null : (attriblist[i]['type']['regex'] ? attriblist[i]['type']['type'] : null) ;
        td2.list=(!attriblist[i]['type']) ? null : (attriblist[i]['type']['list'] ? attriblist[i]['type']['list'] : null) ;
        td2.validator = this.attribute_validator(attriblist[i]) ;
        if (td2.validator)
             td2.className = dsutl.toolwin.validate_to_class(td2.validator(val));
         
        td2.onclick=function(ev) {
            if (document.red) document.red.property_row_focus(ev);
        }
        td2.prop_dvn=attriblist[i];


    }
}

designer.prototype.attribute_validator = function(attr){
  if (!attr['type']) return null;
  if (attr['type']['validator'])  
            return new Function("val", " return " + attr['type']['validator'] + "(val)");
  return null;          
}

designer.prototype.attribute_editor = function(el){
    if (!this.inspectorFrame){
        this.show_property(el);
    }
}

designer.prototype.property_row_focus = function(event){
    
    if (event.target.tagname="td"){
        var td= event.target;
        var value=event.target.innerHTML;
        
        var type = td['type'] ? td['type']  : 0;
        
        if (type<=2 && event.button>0){           
            var retval = dsutl.toolwin.propertydialog(td['name'], value);
            if (retval) 
                this.setProperty(td.prop_dvn,retval);
            event.preventDefault();
            event.stopPropagation();
            return;
        }
        
        switch (type){
            
            case 0:
            case 1:{
                libutil.dom.clearChildNode(td);
                var txtedit = libutil.html.create_input(td, 'text', value);
                if (td.validator){
                    txtedit.className= dsutl.toolwin.validate_to_class(td.validator(txtedit.value));
                    txtedit.validator=td.validator;
                    txtedit.oninput= function(){
                       txtedit.className= dsutl.toolwin.validate_to_class(txtedit.validator(txtedit.value)) 
                    }    
                    }
                break;
            }
            case 2:
            case 3:{
              
                var list=td['list'];
                libutil.dom.clearChildNode(td);        
                libutil.html.create_select(td,'text',value,list,type==3)       
                break;
            }
            default:{
                event.preventDefault();
                event.stopPropagation();
                return;
            }
        }
   
        var edit=event.target.firstElementChild;
        edit.focus();
        edit.oldval=value;
        document.red.property_event(edit);

    
        if (type==3){           
            edit.onchange= function(event){
                var el=event.srcElement;
                if (el.value=='...'){
                    var code = '<input xmlns="http://www.w3.org/1999/xhtml" type="text" value=""></input>';
                    el.onblur=null;
                    var parent=el.parentNode;
                    parent.innerHTML=code;
                    var edit=parent.firstElementChild;
                    edit.focus();
                    edit.oldval=value;                    
                    if (document.red) 
                        document.red.property_event(edit);                         
                    event.preventDefault();
                    event.stopPropagation();
                }
            }        
        }
     
    }
    event.preventDefault();
    event.stopPropagation();   
}


designer.prototype.property_event = function(el){
    
    el.onblur= function() {
        if (document.red) document.red.property_leave_focus(el);
    }
    el.addEventListener( 'keyup' ,function (ev) {       
        if ((ev.keyIdentifier=="Enter"))
            document.red.property_leave_focus(el);
        else 
            event.stopPropagation();
    });    
}


designer.prototype.property_leave_focus = function(el){
    var oldval=el.oldval;
    var value =el.value;
    var td=el.parentNode;
    td.removeChild(el);
    td.innerHTML=value;
    if (oldval!=value){
        this.setProperty(td.prop_dvn,value);
    }
    event.stopPropagation();
    event.stopPropagation();   
}


designer.prototype.setNeedSave = function(){
    this.needsave=true; 
    dsutl.toolwin.setMainWindowToolStatus(1);
}

/*

    Selector wraper

*/



dsutl.selectwraper = function(el){
    this.element = el;
    this.document= el.ownerDocument;
    this.designer= this.document.red;
    this.parent = el.parentNode;
    this.select();
}

dsutl.selectwraper.prototype.getElement = function(){
    return this.element;
}

dsutl.selectwraper.prototype.getDocument = function(){
    return this.document;
}

dsutl.selectwraper.prototype.getParent = function(){
    return this.parent;
}

dsutl.selectwraper.prototype.select = function(){
    
    if (dsutl.SELECT_MODE){ 
        this.selement = this.document.createElementNS(libutil.SVG_NAMESPACE_URL, 'g');    
        this.selement.appendChild(this.parent.replaceChild( this.selement , this.element));}
    else{
        this.selement = this.element;
        this.oldclass=this.selement.getAttribute('class');
    }
    
    this.selement.setAttribute('class', 'designer_selected');
    this.selement.designer=this.designer;
    /*this.selement.addEventListener('keyup', function() {
        if (this.designer) this.designer.keybordDispatcherd(event);
    });*/
    this.selement.onmousemove = function() {
        if (this.designer) this.designer.mousemoveDocument();
    };
    this.selement.onmousedown = function() {
        if (this.designer) this.designer.mousedownComponent();
    };
    this.selement.onmouseup = function() {
        if (this.designer) this.designer.mouseupDocument();
    };
    this.selement.oncontextmenu = function() {
        if (this.designer) {
            if (this.designer.isSelection(this.designer.getTarget(event)))
                this.designer.createContextMenu(event);
            event.preventDefault();
            event.stopPropagation();
        }
    };
}


dsutl.selectwraper.prototype.deselect = function(){
    if (this.selement){
        if (!dsutl.SELECT_MODE)
            this.selement.setAttribute('class', this.oldclass ? this.oldclass : '');
        
     if (dsutl.SELECT_MODE){       
       this.selement.removeChild(this.element); 
       this.parent.replaceChild(this.element,this.selement);
       if (this.designer)
           this.designer.updateElement(this.element);}
       
       this.selement.onmousemove = undefined;
       this.selement.onmousedown = undefined;
       this.selement.onmouseup = undefined;
       this.selement.oncontextmenu  = undefined;
       
    } 
}

dsutl.selectwraper.prototype.shiftRect = function(x, y){
        dsutl.trslt.setShiftXTranslate(this.selement, x);
        dsutl.trslt.setShiftYTranslate(this.selement, y);
}



//  translateutol

dsutl.trslt.getXname =  function (el){
    if (el.hasAttribute('x')) return 'x';
    if (el.hasAttribute('cx')) return 'cx';
    if (el.hasAttribute('d')) return 'd';
    if (el.hasAttribute('transform')) return 'transform';
    return null;
}

dsutl.trslt.getYname =  function (el){
    if (el.hasAttribute('y')) return 'y';
    if (el.hasAttribute('cy')) return 'cy';
    if (el.hasAttribute('d')) return 'd';
    if (el.hasAttribute('transform')) return 'transform';
    return null;
}

dsutl.trslt.getWname =  function (el){
    if (el.hasAttribute('width')) return 'width';
    return null;
}

dsutl.trslt.getHname =  function (el){
    if (el.hasAttribute('height')) return 'height';
    return null;
}


dsutl.trslt.getTmpTranslate =  function (el){
    if (el.hasAttribute('transform')){
        var attr = el.getAttribute('transform');
        if (attr){
            var matchstr = attr.match(/\s*translate\s*\(\s*\-?[0-9\.]+\s*\,\s*\-?[0-9\.]+\s*\)\s*/);
            if (matchstr && matchstr.length==1){
                return attr;
            }
            else{
                return 'translate(0,0) '+attr; 
        }
    }}
    return null;
}




dsutl.trslt.getinfoXTranslate =  function (el){
    var traslateattr = dsutl.trslt.getTmpTranslate(el);
    if (traslateattr){
        try{
        var traslateattr_xmatch =traslateattr.match(/(?:\s*translate\s*\(\s*)/);
        if (traslateattr_xmatch && traslateattr_xmatch.length==1){
            var strt = traslateattr_xmatch[0];
            var rest = traslateattr.substring(strt.length);
            traslateattr_xmatch =rest.match(/(?:\-?[0-9\.]+)/);
            if (traslateattr_xmatch && traslateattr_xmatch.length==1){
                var midle = traslateattr_xmatch[0];
                var stp = rest.substring(midle.length);
                return{
                    'start' : strt,
                    'x' : midle,
                    'stop' : stp}
        }}}
        catch(error){}    
    }
    return null;
}

dsutl.trslt.getXTranslate =  function (el){
    var info = dsutl.trslt.getinfoXTranslate(el);
    //console.log(info);
    if (info){
        return parseFloat(info.x);
    }
    return null;
}

dsutl.trslt.setXTranslate =  function (el, x){
    var info = dsutl.trslt.getinfoXTranslate(el);
    if (info){
        el.setAttribute('transform', info.start + x  + info.stop);
    }
}

dsutl.trslt.setShiftXTranslate =  function (el , x){
    if ((x==null) || (x==undefined) || (x==0)) return;
    var info = dsutl.trslt.getinfoXTranslate(el);
    if (info){
        el.setAttribute('transform', info.start + (x + parseFloat(info.x)).toString() + info.stop);       
    }
    else{
        el.setAttribute('transform', 'translate('+x.toString() + ',0)');
    }
}

dsutl.trslt.getinfoYTranslate =  function (el){
    var traslateattr = dsutl.trslt.getTmpTranslate(el);
    if (traslateattr){
        try{
        var traslateattr_xmatch =traslateattr.match(/(?:\s*translate\s*\(\s*\-?[0-9\.]+\s*\,)/);
        if (traslateattr_xmatch && traslateattr_xmatch.length==1){
            var strt = traslateattr_xmatch[0];
            var rest = traslateattr.substring(strt.length);
            traslateattr_xmatch =rest.match(/(?:\-?[0-9\.]+)/);
            if (traslateattr_xmatch && traslateattr_xmatch.length==1){
                var midle = traslateattr_xmatch[0];
                var stp = rest.substring(midle.length);
                return{
                    'start' : strt,
                    'y' : midle,
                    'stop' : stp}
        }}}
        catch(error){}    
    }
    return null;
}

dsutl.trslt.getYTranslate =  function (el){
    var info = dsutl.trslt.getinfoYTranslate(el);
    if (info){
        return parseFloat(info.y);
    }
    return null;
}

dsutl.trslt.setYTranslate =  function (el, y){
    var info = dsutl.trslt.getinfoYTranslate(el);
    if (info){
        el.setAttribute('transform', info.start + y  + info.stop);
    }
}


dsutl.trslt.setShiftYTranslate =  function (el , y){
    if ((y==null) || (y==undefined) || (y==0)) return;
    var info = dsutl.trslt.getinfoYTranslate(el);
    if (info){
        el.setAttribute('transform', info.start + (y + parseFloat(info.y)).toString() + info.stop);       
    }
    else{
        el.setAttribute('transform', 'translate(0,'+y.toString() + ')');
    }
}




dsutl.trslt.getDXinfo =  function (el){
    if (el.hasAttribute('d')) {
        var dpath = el.getAttribute('d');
        var fnd = dpath.match(/\s*M[\-0-9\s\.\,]+/);
        if (fnd && (fnd.length>0))  {   
            var dpath_strt = dpath.substring(0,fnd[0].length);
            var dpath_stp = dpath.substring(fnd[0].length, dpath.length );
            fnd = dpath_strt.match(/\s*M\s*[\-0-9\.]+/);
            if (fnd && (fnd.length>0))  {
                dpath_stp = dpath_strt.substring(fnd[0].length, dpath_strt.length ) + dpath_stp;
                fnd = dpath_strt.match(/\s*M\s*(?=[\-0-9\.]+)/);
                if (fnd && (fnd.length>0))  {
                    var dpath_val = dpath_strt.substring(fnd[0].length, dpath_strt.length );
                    dpath_strt = dpath_strt.substring(0,fnd[0].length);
                    fnd = dpath_val.match(/\s*(?=([\-0-9\.])+)/);
                    if (fnd && (fnd.length>0))  {                    
                        dpath_val = dpath_val.substring(fnd[0].length, dpath_val.length );
                        fnd = dpath_val.match(/\s*[\-0-9\.]*/);
                        if (fnd && (fnd.length>0))  { 
                            dpath_val = dpath_val.substring(0, fnd[0].length); 
                               return {
                                   'start' : dpath_strt,
                                   'x' : dpath_val,
                                   'stop' :  dpath_stp
                                   
                               };
                        }
                    }
                }                                       
            }
        }
    };
    return null;
}

dsutl.trslt.getDXval =  function (el){
    if (el.hasAttribute('d')) {
        try{
        var dpathinfo = dsutl.trslt.getDXinfo(el);
        if (dpathinfo)
            return parseFloat(dpathinfo.x);}
        catch(error){}
    }
    return null;
}

dsutl.trslt.setDXval =  function (el , x){
    if (el.hasAttribute('d')) {
        var dpathinfo = dsutl.trslt.getDXinfo(el);
        if (dpathinfo)
            el.setAttribute('d', dpathinfo.start + (x).toString() + dpathinfo.stop);
    }
}


dsutl.trslt.getDYinfo =  function (el){
    if (el.hasAttribute('d')){
        var dpath = el.getAttribute('d');
        var fnd = dpath.match(/\s*M[\-0-9\s\.\,]+/);
        if (fnd && (fnd.length>0))  {   
            var dpath_strt = dpath.substring(0,fnd[0].length);
            var dpath_stp = dpath.substring(fnd[0].length, dpath.length );
            fnd = dpath_strt.match(/\s*M\s*[\-0-9\.]+(\s|\,)/);
            if (fnd && (fnd.length>0))  {
                var dpath_val = dpath_strt.substring(fnd[0].length);
                dpath_strt = dpath_strt.substring(0,fnd[0].length);
                fnd = dpath_val.match(/[\-0-9\.]+/);
                if (fnd && (fnd.length>0))  {                    
                    dpath_val = fnd[0];
                    try{
                        return {
                            'start' : dpath_strt,
                            'y' : dpath_val,
                            'stop' :  dpath_stp
                                   
                        };
                    }
                    catch(error){}
                }
            }
        }
    };
    return null;
}

dsutl.trslt.getDYval =  function (el){
    if (el.hasAttribute('d')) {
        try{
        var dpathinfo = dsutl.trslt.getDYinfo(el);
        if (dpathinfo)
            return parseFloat(dpathinfo.y);}
        catch(error){}
    }
    return null;
}


dsutl.trslt.setDYval =  function (el , y){
    if (el.hasAttribute('d') && y) {
        var dpathinfo = dsutl.trslt.getDYinfo(el);
        if (dpathinfo)
            el.setAttribute('d', dpathinfo.start + (y).toString() + dpathinfo.stop);
    }
}





/*

    Component info from schema

*/


dsutl.componentinfo.prototype.init = function(libsulr){
    try{
        this.libsdoc=libutil.dom.readDoc(libsulr);
        if (this.libsdoc){
            this.libs.push('../util/lib.xsd')
            var els=this.libsdoc.getElementsByTagName('include');
            for (var i=0; i<els.length;++i)
                if (els[i].getAttribute('xsi:schemaLocation')) 
                    this.libs.push(els[i].getAttribute('xsi:schemaLocation'));

       
            if (this.libs.length>0)
                for (var i=0; i<this.libs.length;++i)
                    this.initlibs(this.libs[i]);   
        }
    }
catch(error){
    alert('Error load library schemas :' + error);
}
}



dsutl.componentinfo.prototype.targetNSprefix = function(doc){
    if (doc){
        var docel=doc.documentElement;
        if (docel && docel.hasAttribute('targetNamespace')) { 
        var uri=docel.getAttribute('targetNamespace');
        if (docel.attributes){
        for (var i=0; i< docel.attributes.length; ++i){ 
            if ((docel.attributes[i].localName!='targetNamespace') 
                    && (docel.attributes[i].value==uri))
             return docel.attributes[i].localName;}}}}
    return null;}



dsutl.componentinfo.prototype.initlibs = function(libulr){
    var libdoc=libutil.dom.readDoc(libulr);
    var pref = this.targetNSprefix(libdoc);
    if (libdoc){ 
        this.read_types(libdoc,pref);
        this.read_elements(libdoc, pref);
        this.read_creators(libdoc);
    }
}





dsutl.componentinfo.prototype.getAttributeList = function (el){ 
    
    var node = el['nodeName'];
    if ((node) && (this.elements[node]!=undefined))
        return this.elements[node];

    this.attributes_for_nullschema(el);
    return this.elements[node];

    
}


dsutl.componentinfo.prototype.attributes_for_nullschema = function (el){ 

    var result =[];
    for (var i=0; i< el.attributes.length; ++i){
        result.push({
            'name' : el.attributes[i].name , 
            'type' : null, 
            'use' : null, 
            'default' : null
        })
                
        return result;
    }
}

dsutl.componentinfo.prototype.read_types =  function(doc, pref){
    if (doc){
        var docElement=doc.documentElement;
        var els=doc.getElementsByTagName('simpleType');
        for (var i=0; i<els.length;++i){
            if ((els[i].parentNode==docElement) && (els[i].getAttribute('name'))){
                var info=this.read_simple_type(els[i]);
                var nm = els[i].getAttribute('name');
                nm = pref ? (pref + ':' + nm) : nm; 
                if (info)
                    this.types[nm] = {
                        'name' : nm , 
                        'type' : info.type, 
                        'base' : info['base'], 
                        'regex' : info['regex'],  
                        'list' : info['list'],
                        'validator': (els[i] && els[i].hasAttributeNS(libutil.LIB_NAMESPACE_URL,'validator') ? 
                            els[i].getAttributeNS(libutil.LIB_NAMESPACE_URL,'validator') : null)
                    };
                    
            }
            else
                this.types[nm] = {
                    'name' : nm , 
                    'type' : 0, 
                    'base' : null, 
                    'regex' : null,  
                    'list' : null
                } 
        }
    }
}

dsutl.componentinfo.prototype.read_simple_type =  function(el){
    if (el){
        var restrictel=el.firstElementChild;
        if ((restrictel) && (restrictel.localName=='restriction')){
            return this.read_restriction_type(restrictel,el);
        }
    }
    return {
        'type': 0, 
        'base': null, 
        'regex': null, 
        'list': null
    };
}

dsutl.componentinfo.prototype.read_restriction_type =  function(el, prnt){
    if ((!el) || (el.childElementCount==0))
        return {
            'type': 0, 
            'base': null, 
            'regex': null, 
            'list': null
        };
    var type=0;
    var base=el.getAttribute('base');
    var list=null;
    var regex=null;
        
    if (el.childElementCount==1){
        if ((el.firstElementChild.localName='pattern') && (el.firstElementChild.getAttribute('value'))){
            type=1;
            regex=el.firstElementChild.getAttribute('value');
        }           
    }
    else{
        if (el.firstElementChild.localName=='enumeration'){
            list = [];
            type=2;
            for (var ch=el.firstElementChild; ch; ch=ch.nextElementSibling){
                if (ch.localName=='enumeration'){
                    if (ch.getAttribute('value')!=null)
                        list.push(ch.getAttribute('value'));
                    else
                        type=3;
                }
            }
            if (list.length==0){
                list=null;
                type=0;
            }
        } 
    }
    return {
        'type': type, 
        'base': base, 
        'regex': regex, 
        'list': list
    };
}
            
            
     

dsutl.componentinfo.prototype.read_elements =  function(doc, pref){
    if (doc){
        var els=doc.getElementsByTagName('element');
        for (var i=0; i<els.length;++i){
            if (els[i] && (els[i].parentNode==doc.documentElement)){
            var nm = els[i].getAttribute('name');
            nm = pref /*&& nm!='svg'*/ ? (pref + ':' + nm) : nm;
            if (nm){
                this.elements[nm]={
                    'name' : els[i].getAttribute('name'),
                    'type' : els[i].getAttribute('type'),
                    'attributes' : null
                };
                this.read_attributes(els[i],this.elements[nm]);
            }
        }
    }}
}

dsutl.componentinfo.prototype.read_attributes = function(el,  info){
    var result = {};
    if (!el)
        return result;
    var typeel= libutil.dom.findChildByTagName(el,'complexType');
    if (!typeel) return;
        
    for (var ch=typeel.firstElementChild; ch; ch=ch.nextElementSibling)
        if ((ch.localName=='attribute') && (ch.getAttribute('name')))
            result[ch.getAttribute('name')] = {
                'name' : ch.getAttribute('name') , 
                'type' : this.get_attribute(ch.getAttribute('type')), 
                'use' : ch.getAttribute('use'), 
                'default' : ch.getAttribute('default'),
                'typename' : ch.getAttribute('type')
            };
                
    info.attributes=result;
}

dsutl.componentinfo.prototype.get_attribute = function(name){
    return ( name && this.types[name]) ? (this.types[name]) : null;
}


dsutl.componentinfo.prototype.read_creators =  function(doc){
   if (doc){
        var els=doc.getElementsByTagName('creator');
        for (var i=0; i<els.length;++i)
            if (els[i].nodeName=='lib:creator'){
                var nm = els[i].getAttribute('name');
                var el = els[i].firstElementChild;
                if ((nm) && (nm!='') && (el))
                    this.creators[nm] = {
                        'name' : nm , 
                        'template' : el
                    };
                    
            }        
    }
}


            
/*


    Main disigner interface


*/               
                
                
dsutl.toolwin.getMainWindow = function (){
    libutil.www.create_tbwindow('maintool', 'Редактор' ,'100' , '100', '600','64','yes','yes',null,null,
        ['save','objinsp', 'forminsp','libinsp', 'exit'],
        ['Сохранить','Редактор свойств', 'Редактор форм','Панель компонентов', 'Выход'],
        [function() {
            dsutl.toolwin.SaveAll();
        },
        function() {
            dsutl.toolwin.resetObjectInspector();
        },
        function() {
            dsutl.toolwin.resetFormInspector();
        },
        function() {
            dsutl.toolwin.resetLibInspector();
        },           
        function() {
            dsutl.toolwin.destroyMainWindow();
        }],
        dsutl.toolwin.destroyMainWindow);
        
        
    var tmp=$$global();
 
    dsutl.toolwin.setMainWindowToolStatus();
    tmp.maintool.focus();
    
}




dsutl.toolwin.setMainWindowToolStatus = function (val){ 
    if ((val==1 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'save', dsutl.toolwin.isNeedSave() ?  'on' :  'disabled');
    if ((val==2 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'objinsp', dsutl.toolwin.getObjectInspector() ?  'off' :  'on');
    if ((val==3 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'forminsp', dsutl.toolwin.getFormInspector() ?  'off' :  'on');
    if ((val==4 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'libinsp', dsutl.toolwin.getLibInspector() ?  'off' :  'on');
}


dsutl.toolwin.destroyMainWindow = function(){
    var tmp=$$global();
    if (tmp && tmp.maintool)
        tmp.maintool=undefined;
    if (!dsutl.toolwin.isNeedSave()){          
        $$exit();
        return;
    }
    if (confirm("Выйти без сохранения?")){
        $$exit();
        return;
    } 
    else{
        setTimeout(function() {
            dsutl.toolwin.getMainWindow();
        }, 10);
    }
}


///  Object inspector

dsutl.toolwin.getObjectInspector = function (force){
    var tmp=$$global();
    if (!force && !tmp.objectinspectorwin) return null;
    if (tmp && !tmp.objectinspectorwin){
        var objectinspectorwin=libutil.window.createhtml('_ObjectInspector','Свойства','100', '900', '400','650','yes','yes',null,null, "../util/css/objectinspector.css");
        tmp.objectinspectorwin=objectinspectorwin;
        tmp.objectinspectordoc=objectinspectorwin.document;
        objectinspectorwin.onunload=dsutl.toolwin.destroyObjectInspector;
        var objdoc =objectinspectorwin.document;
        var body=objdoc.getElementsByTagName('body')[0];
        var div = libutil.html.create_div(libutil.html.create_div(body),null,"scrollWrapper");
        var table = libutil.html.create_table(div,null,"scrollable");
        var tbody = libutil.html.create_tbody(table);
        var tr = libutil.html.create_tr(tbody);
        var th1 =libutil.html.create_th(tr);
        th1.innerHTML='Имя';
        var th2 =libutil.html.create_th(tr);
        th2.innerHTML='Значение';
        tmp.objectinspectortbody=tbody;
        var current=dsutl.toolwin.getCurrentRedactor();
        if (current)
            current.show_property();
              
    }   
    return (tmp && tmp.objectinspectorwin) ? tmp.objectinspectorwin : null;
}

dsutl.toolwin.resetObjectInspector = function(){
    var vis =  dsutl.toolwin.getObjectInspector();
    var tmp=$$global();
    if (vis && tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
    else
        dsutl.toolwin.getObjectInspector(true);
    dsutl.toolwin.setMainWindowToolStatus(2);
        
} 

dsutl.toolwin.getObjectInspectorDocument = function(){
    var tmp = $$global();
    if (tmp && tmp.objectinspectordoc) {
        return tmp.objectinspectordoc; 
    }
}

dsutl.toolwin.getObjectInspectorTbody = function(){
    var tmp = $$global();
    if (tmp && tmp.objectinspectortbody) {
        return tmp.objectinspectortbody;       
    }   
}  


dsutl.toolwin.showObjectInspector = function(){
    var tmp = dsutl.toolwin.getObjectInspector();
    if (tmp)
        tmp.focus();
}



dsutl.toolwin.closeObjectInspector = function(){
    var tmp = dsutl.toolwin.getObjectInspector();
    if (tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
}

dsutl.toolwin.destroyObjectInspector = function(){
    var tmp=$$global();
    if (tmp && tmp.objectinspectorwin)
        tmp.objectinspectorwin=undefined;
    if (tmp && tmp.objectinspectordoc)
        tmp.objectinspectordoc=undefined;
    if (tmp && tmp.objectinspectortbody)
        tmp.objectinspectortbody=undefined;
    dsutl.toolwin.setMainWindowToolStatus(2);
    
}


// Form inspector


dsutl.toolwin.getFormInspector = function (force){
    var tmp=$$global();
    if (!tmp.formtool && !force) return null;
    if (tmp && !tmp.formtool){

        libutil.www.create_tbwindow('formtool', 'Окна' ,'600','100', '600','200','yes','yes',null,null,
            ['add', 'new'],
            ['Добавить из файла','Новая форма'],
            [
            function() {
                dsutl.toolwin.addwindowfromfile();             
            },
            function() {
                dsutl.toolwin.addnewwindow();
            }]);
    
        var objdoc =tmp.formtool.document;
        tmp.formtool.onunload=dsutl.toolwin.destroyFormInspector;

        var body=objdoc.getElementsByTagName('body')[0];
        var head=objdoc.getElementsByTagName('head')[0];
        libutil.html.create_link(head, 'stylesheet', 'text/css',"../util/css/forminspector.css");
        var div = libutil.html.create_div(libutil.html.create_div(body),null,"scrollWrapper");
        var table = libutil.html.create_table(div,null,"scrollable");
        var tbody = libutil.html.create_tbody(table);
        libutil.html.create_tr(tbody);
        tmp.formtooltbody=tbody;
    }
 
    dsutl.toolwin.fillFormInspector();
    return (tmp && tmp.formtool) ? tmp.formtool : null;
}

dsutl.toolwin.resetFormInspector = function(){
    var vis =  dsutl.toolwin.getFormInspector();
    var tmp=$$global();
    if (vis && tmp.formtool)
        tmp.formtool.close();
    else
        dsutl.toolwin.getFormInspector(true);
    var tmp=$$global();
    tmp.formtool.focus();
    dsutl.toolwin.setMainWindowToolStatus(3);
        
} 

dsutl.toolwin.fillFormInspector = function (){
    var tmp=$$global();
    var tbody = tmp.formtooltbody;
    
    libutil.dom.clearChildNode(tbody);   

    var tr = libutil.html.create_tr(tbody);
    
    libutil.html.create_tabel_header(tr,null,null,
        ['Файл','id','caption','x','y','width','height','visible','alltop','resize','decorate','modal','0/X','-']);
   
    var fl= libutil.global.getFormList();
 
                            
    for (var i=0; i<fl.length; ++i ){
        var formname=fl[i]['name'];
        formname=formname.toString();
        var tr= libutil.html.create_tr(tbody);
       
        var td1= libutil.html.create_td(tr);
        td1.innerHTML=fl[i]['file'] ? fl[i]['file'] : "";
        
        td1.className='static';
   
        dsutl.toolwin.fiCreateRow(tr,fl[i],'name');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'caption');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'left', '50px');       
        dsutl.toolwin.fiCreateRow(tr,fl[i],'top', '50px');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'width', '50px');       
        dsutl.toolwin.fiCreateRow(tr,fl[i],'height', '50px'); 
        dsutl.toolwin.fiCreateRow(tr,fl[i],'visible', '50px');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'allwaystop', '50px');       
        dsutl.toolwin.fiCreateRow(tr,fl[i],'resizable', '50px');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'decorated', '50px');
        dsutl.toolwin.fiCreateRow(tr,fl[i],'modal', '50px');        
        
        var td11= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btno = libutil.html.create_button( td11,'height: 15px;',null,'');
        btno.setAttribute('onclick','dsutl.toolwin.resetwindow("'+formname+ '");');
 
        
        var td13= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btnd = libutil.html.create_button( td13,'height: 15px;',null,'');
        btnd.setAttribute('onclick','dsutl.toolwin.removeFormFromProject("'+formname+ '");');
    
    }
}

dsutl.toolwin.fiCreateRow = function(tr, tblrow, name, width, lst){
    var td= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0;' + width ? 'width: ' + width + ';' : '');
    var tmp= tblrow[name] ? tblrow[name] : '';
    if (lst)
        td.lst=lst; 
    td.innerHTML= tmp;
    td.elem=tblrow;
    td.value=tmp;
    td.propname=name;
    td.onclick=function(ev) {
        dsutl.toolwin.fiPropertyRowFocus(ev);    
    }
}



dsutl.toolwin.fiPropertyRowFocus = function(ev){
    try{
        var td = ev.target;
        libutil.dom.clearChildNode(td);
        if (td.lst)
            var edit=libutil.html.create_select(ev.target, 'text', td.value, td.lst);
        else
            var edit=libutil.html.create_input(ev.target, 'text', td.value);
       
    
        edit.focus();
        edit.oldval=td.value;  
 
        edit.onblur= function(ev) {
            dsutl.toolwin.fiPropertyLeaveFocus(ev);
        }

        edit.addEventListener( 'keyup' ,function (ev) {       
            if ((ev.keyIdentifier=="Enter"))
                dsutl.toolwin.fiPropertyLeaveFocus(ev);
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

dsutl.toolwin.validate_to_class = function(val){
   if (val==true) return 'ok';
   if (val==false) return 'error';
   return 'nodef';
}

dsutl.toolwin.fiPropertyLeaveFocus = function(event){

    if (!event.target) return;
    var oldval=event.target.oldval;
    var value =event.target.value;
    var td=event.target.parentNode;
    td.removeChild(event.target);
    td.innerHTML=value;
    if ((oldval!=value) && (dsutl.toolwin.fiCheckFormParam(td.propname,value))){  
        
        
        if (td.elem && td.elem['element']){     
            
            td.elem['element'].setAttribute(td.propname,value);
            td.elem[td.propname]=value;
            dsutl.toolwin.closewindow(td.elem['name'], true);
            td.elem['param'] = libutil.project.buildparam(td.elem['element']);
            dsutl.toolwin.openwindow(td.elem['name']);

            
        }
        var fdoc = libutil.global.getStartupDoc();
        fdoc.needsave=true;
        dsutl.toolwin.setMainWindowToolStatus();

    }

          
    event.preventDefault();
    event.stopPropagation();   
}

 

dsutl.toolwin.fiCheckFormParam = function(name, val){
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
            return !libutil.project.getFormInfo(val);
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



dsutl.toolwin.destroyFormInspector = function(){
    var tmp=$$global();
    if (tmp && tmp.formtool)
        tmp.formtool=undefined;
    if (tmp && tmp.formtooltbody)
        tmp.formtooltbody=undefined; 
    dsutl.toolwin.setMainWindowToolStatus(3);  
}

//


dsutl.toolwin.getLibInspector = function (force){    
    var tmp=$$global();
    if (tmp && !tmp.libtool && !force) return null;
    if (!tmp.libtool){
        var libs =libutil.global.getLibList();
        
        var heigth = libs.length>0 ? 86 + 52 * (libs.length-1) : 46;
        
        libutil.www.create_tbwindow('libtool','Библиотека','300','100', '600',heigth,'yes','yes',null,null);
        tmp.libtool.onunload=dsutl.toolwin.destroyLibInspector;
    
        var libs =libutil.global.getLibList();
        for (var i=0; i<libs.length;++i){
            var lib =libs[i];
            var btnsname =[];
            var btnsfunc =[];
            var btnshint =[];
            var comps =lib.components;        
            for (var j=0; j<comps.length;++j){
                btnsname.push(comps[j].hint);
                btnsfunc.push(dsutl.toolwin.setSelectedToolEvent);
                btnshint.push(comps[j].hintup);
            }        
            libutil.www.create_tbwindow_tools('libtool', lib.name , 
                btnsname, 
                btnshint, 
                btnsfunc, 
                null, 
                lib.caption, 
                "background-color: #E7E7E7; margin: 0px; border-width: 1px 0px ; border-color: yellow; border-style: solid; text-align: center; color: #040347)"); 
        }
        
    //tmp.libtool.onload= function() {alert('test');}

    }
    return (tmp && tmp.libtool) ? tmp.libtool : null;

}  



dsutl.toolwin.resetLibInspector = function(){
    
    var tmp=$$global();
    if (tmp.libtool)
        tmp.libtool.close();
    else
        dsutl.toolwin.getLibInspector(true);
    var tmp=$$global();
    tmp.libtool.focus();
    dsutl.toolwin.setMainWindowToolStatus(4);     
} 

dsutl.toolwin.setSelectedToolEvent = function(event){
    if (event && event.target && event.target.parentNode){
        var trgt=event.target.parentNode;
        dsutl.toolwin.setSelectedComponent(trgt.nametool, trgt.namebtn);
    }
}

dsutl.toolwin.setSelectedComponent = function(tool, comp){
    //alert(tool + ' : ' + comp);
    var tmp= $$global(); 
    var set  = tool && comp;
    var result = null; 
    if (tmp){
        var select = tmp['selectedComponent'];       
        if (select && set && select.tool==tool && select.component==comp){
            tmp['selectedComponent'] =  null;
            libutil.www.set_tbwindow_btnstatus(tool, tool , comp , 'on' );
            return null;
        }
       
        if (select){ 
            
            libutil.www.set_tbwindow_btnstatus(select.tool, select.tool  , select.component  , 'on' );
            result = {
                'tool' : select.tool , 
                'component' : select.component
            };
            if (!set) return result;
            libutil.www.set_tbwindow_btnstatus(tool, result.tool , result.component , 'on' );
        }
        if (set){
            tmp['selectedComponent']={
                'tool' : tool , 
                'component' : comp
            };
            libutil.www.set_tbwindow_btnstatus(tool, tool  , comp  , 'off' );
        }
    }
    return result;
}


dsutl.toolwin.getSelectedComponent = function(){
    var tmp = dsutl.toolwin.setSelectedComponent();
    return (tmp && tmp.tool && tmp.component)? libutil.project.get_components(tmp.tool, tmp.component): null;
}

dsutl.toolwin.clearSelectedComponent = function(){
    var tmp= $$global();
    tmp['selectedComponent']=undefined;
}


dsutl.toolwin.destroyLibInspector = function(){
    var tmp=$$global();
    if (tmp && tmp.libtool)
        tmp.libtool=undefined;
    dsutl.toolwin.setMainWindowToolStatus(4);  
}



//

dsutl.toolwin.openwindow = function(name){
    var fl =  libutil.global.getFormList();
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


dsutl.toolwin.closewindow = function (name){
    var fl =  libutil.global.getFormList();
   
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

dsutl.toolwin.resetwindow = function (name){
    var fl =  libutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i){
            try{
                if (fl[i]['name']==name){
                    if (fl[i].window)
                        dsutl.toolwin.closewindow(name);
                    else
                        dsutl.toolwin.openwindow(name);              
                }
            }
            catch(error){
                alert(error);
            }
        }
    }
}

dsutl.toolwin.windowstatus = function (name){
    var fl =  libutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i)
            if (fl[i]['name']==name)
                return fl[i].window ? true : false;
    }
    return false;
}

dsutl.toolwin.SaveAll = function(){ 
    var fl= libutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red){
            fl[i].red.save();
        }   
    }
    var fdoc = libutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) {
        libutil.dom.writeDoc(fdoc);
        fdoc = libutil.global.getStartupDoc();
        fdoc.needsave=undefined;
    }    
    dsutl.toolwin.setMainWindowToolStatus();
}

dsutl.toolwin.isNeedSave = function (){
    var fl= libutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red && fl[i].red.needsave)
            return true;        
    }   
    var fdoc = libutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) return true;
    return false;
}

dsutl.toolwin.setCurrentRedactor = function (win){
    var tmp= $$global();
    if (!win){
        tmp.currentred = null;
        return;
    }
    var fl =  libutil.global.getFormList();
    if (fl){   
        for (var i=0; i<fl.length;++i){
            if (fl[i]['window']==win){
                tmp.currentred=fl[i]['designer_glb'];  
            }
        }
    }
}

dsutl.toolwin.getCurrentRedactor = function (){
    var tmp= $$global();
    return tmp.currentred;
}

dsutl.toolwin.findwindow = function (name){
    var fl =  libutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                return fl[i].window;
            }
        }
    }
    return null;   
}

dsutl.toolwin.windowexists = function (name){
    var fl =  libutil.global.getFormList();
    if (fl){  
        for (var i=0; i<fl.length;++i){
            if (fl[i]['name']==name){
                return true;
            }
        }
    }
    return false;   
}



dsutl.toolwin.addwindowfromfile = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return; 
    var openddoc = libutil.dom.readDoc(openfile);
    if (!openddoc){
        alert('Документ '+openfile+' не был открыт!');
        return;
    }
    var openform= prompt('Введите имя формы','');
    if (!openform || openform=='') return; 
    if (!libutil.regex.check(openform,'[A-Za-z][A-Za-z0-9]*')){
        alert('Имя формы '+openform+' некорректно!');
        return;
    }
    if (dsutl.toolwin.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    dsutl.toolwin.addform(openfile,openform); 
}
               
dsutl.toolwin.addnewwindow = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return;          
    if (!libutil.regex.check(openfile,'[A-Za-z][A-Za-z0-9]*\\.(xml|html|htm)')){
        alert('Имя формы '+openfile+' некорректно!');
        return;
    }
               
    var openddoc = libutil.dom.readDoc(openfile);
    if (openddoc){
        alert('Документ '+openfile+' уже существует!!');
        return;
    }
               
    var openform= prompt('Введите имя формы','');
    if (!openform || openform=='') return;
    if (!libutil.regex.check(openform,'[A-Za-z][A-Za-z0-9]*')){
        alert('Имя формы '+openform+' некорректно!');
        return;
    }
    if (dsutl.toolwin.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    dsutl.toolwin.createfileform(openfile);
    dsutl.toolwin.addform(openfile,openform);
           
}

dsutl.toolwin.addform = function(file, name){
    try{       
        var doc = libutil.global.getStartupDoc();
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
        libutil.project.addtoformlist(newel);
        dsutl.toolwin.fillFormInspector();
        var fdoc = libutil.global.getStartupDoc();
        if (fdoc && !fdoc.needsave) fdoc.needsave=true;
        dsutl.toolwin.setMainWindowToolStatus();
    }
    catch(error){
        alert(error);
    }
       
}

dsutl.toolwin.createfileform = function(file){
    var tmp=$$global();
    var prjpath=tmp.projectPath;
    var txt = '<?xml-stylesheet href="../util/lib.xsl" type="text/xsl"?>\n'+
    '<svg:svg xmlns="http://www.w3.org/2000/svg"  xmlns:svg="http://www.w3.org/2000/svg" xmlns:mlib="http://dvnci/mlib" xmlns:xlink="http://www.w3.org/1999/xlink"'+ 
    'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" id="root" width="100%" height="100%" style="">\n'+
    '</svg:svg>\n';
    return $$writefile(prjpath.toString()+file,txt);      
}


dsutl.toolwin.removeFormFromProject =function(name){
    if (confirm('Удалить форму "'+name+'" из проекта?')){
        try{
            var fl =  libutil.global.getFormList();
            if (fl){  
                for (var i=0; i<fl.length;++i){
                    if (fl[i]['name']==name){
                        dsutl.toolwin.closewindow(name);
                        libutil.util.remove_element_arr(fl,i);               
                        var fdoc = libutil.global.getStartupDoc();
                        var projel=fdoc.getElementsByTagName('project')[0];
                        var els=fdoc.getElementsByTagName('form');
                
                        for (var j=0; j<els.length;++j){
                            if (els[j].getAttribute('name')==name){
                                els[j].parentNode.removeChild(els[j]);
                                dsutl.toolwin.fillFormInspector();
                                if (fdoc && !fdoc.needsave) fdoc.needsave=true;
                                dsutl.toolwin.setMainWindowToolStatus();
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

dsutl.toolwin.propertydialog = function(name, value){
    return libutil.window.create_modal('../util/html/propertydialog.html',name , value, '20%', '20%', '60%', '60%', '1', 'yes');       
}                
                
                
                
                
  
        
                        
