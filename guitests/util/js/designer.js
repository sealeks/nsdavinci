var designutil = {};
///
designutil.componentinfo = function(){
    this.elements = new Object();
    this.types = new Object();
    this.libs = [];
    this.creators = new Object();;
}

designutil.toolwin = {};
        

///

function designer(doc){ 
    this.instantdocument=doc;
    this.schema=new designutil.componentinfo();
    this.schema.init('../util/lib.xsl');
    this.getSourseDocument();
    this.getLightDocument();
    this.instantdocument.addEventListener('keyup' ,function (ev) {
        document.red.keybord_dispatcher(ev)
    });
    this.instantdocument.addEventListener('mousemove' ,function (ev) {
        document.red.mousemove_document(ev)
    });
    this.instantdocument.addEventListener('mousedown' ,function (ev) {
        document.red.mousedown_document(ev)
    });
    this.instantdocument.addEventListener('mouseup' ,function (ev) {
        document.red.mouseup_document(ev)
    });    
    this.instantdocument.addEventListener('contextmenu' ,function (ev) {
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
            el.onclick = function(ev) {
                if (document.red){
                    document.red.clearSelections();
                    document.red.click_parented(ev);
                    designutil.toolwin.setCurrentRedactor(window);
                    }
            };
        }
        else{
            if (el.id!=""){
                el.oldoncick = el.oncick;
                el.onclick= function() {
                    if (document.red) document.red.click_component(event)
                };
                
                el.addEventListener('keyup', function() {
                    if (document.red) document.red.keybord_dispatcher(event);
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
                el.oldonmousemove = el.onmousemove;
                el.onmousemove = function() {
                    if (document.red) document.red.onmosnopropogate();
                };
                el.oldonmousedown = el.onmousedown;
                el.onmousedown = function() {
                    if (document.red) document.red.mousedown_component();
                };
                el.oldonmouseup = el.onmouseup;
                el.onmouseup = function() {
                    if (document.red) document.red.onmosnopropogate();
                };
                el.oldoncontextmenu = el.oncontextmenu;
                el.oncontextmenu = function() {
                    if (document.red) {
                        if (document.red.isSelection(document.red.getTarget(event)))
                            document.red.createContextMenu(event);
                        event.preventDefault();
                        event.stopPropagation();
                    }
                };
            }
        }        
    }
    catch(except){}
    for (var i=0;i<el.childNodes.length;i++){
        this.attach(el.childNodes[i]); 
    }
}


//  чтение документа источника
designer.prototype.getSourseDocument = function (){ 
    if (this.sourseDocument)
        return this.sourseDocument;
    try{
        this.sourseDocument = libutil.document.readDoc(this.instantdocument.URL);
        if ((this.sourseDocument) && (this.sourseDocument.childNodes.length>1)){
            if (this.sourseDocument.childNodes[0].target=='xml-stylesheet'){
                if (this.sourseDocument.childNodes[0].data)
                    this.readXsltDocument(this.sourseDocument.childNodes[0].data);
            }
        }
    }
    catch(except){
        this.sourseDocument = null;
    }
    return this.sourseDocument;
}



designer.prototype.getLightDocument = function (){ 
    try{
        this.lightDocument = libutil.document.readDoc(this.instantdocument.URL);
        
    }
    catch(except){
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
                this.soursexslt = libutil.document.readDoc(urlxslt);
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
    
    while ((el!=owndoc) && (!el.getAttribute('id')) && (el.parentNode))
        el=el.parentNode;

    return ((el==owndoc)) || (!el.getAttribute('id')) ? undefined : el;
}

designer.prototype.check_is_parent = function (el, self){
    var tst=el;
    if ((!tst) || (tst===this.instantdocument.documentElement)) return false;
    while (tst.parentNode!==this.instantdocument.documentElement){
        if (tst.parentNode==self)
            return true;
        tst=tst.parentNode;
    }
    return false;
}



designer.prototype.unicalIdGenerate = function(el, doc) {
    var i=0;
    var tmpl = 'name';
    var expr = new RegExp('[a-z]{1,}', 'i');
    if (el && (el.getAttribute('id')))
        tmpl=expr.exec(el.getAttribute('id'));

    if (tmpl=='') tmpl = 'name';
   
    var fid=tmpl + i;
    while (doc.getElementById(fid))
        fid=tmpl+ (++i);
    
    return fid;
}


designer.prototype.getAttributeList = function(el) {
    if (el){
        return this.schema.getAttributeList(this.getSourseElement(el));
    }
    else
    {
        var result = [];
        if ((!this.selectedElemens ) || (this.selectedElemens.length==0)) return;
        var attrs = []; 
        for (var j=0; j< this.selectedElemens.length; ++j){
            var attr = this.getAttributeList(this.selectedElemens[0]);
            if (!attr) 
                return null;
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
        return undefined;
    var sel = this.getSourseElement(this.selectedElemens[0]);
    if (sel){
        var value=sel.getAttribute(name);
        value= value !=null ? value : undefined;
        if (this.selectedElemens.length>1){
            for (var j=1; j< this.selectedElemens.length; ++j){
                var val=this.getAttributeValue(name, this.selectedElemens[j]);
                val= val !=null ? val : undefined;
                if (value!=val)
                    return undefined;
            } 
        }
        return value!=undefined ? value : '';
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
    if ((!this.selectedElemens ) || (this.selectedElemens.length==0)) 
        return;
    
    for (var j=0; j< this.selectedElemens.length; ++j){
        this.setAttributeValue(name,val, this.selectedElemens[j], true);
    }
  
}


designer.prototype.setProperty = function(nm, val){
    this.setAttributeValue(nm['name'],val);
    this.updateElement();
    this.setNeedSave();
    designutil.toolwin.setMainWindowToolStatus(1);
    this.show_property();
    
    
}    


designer.prototype.getXname =  function (el){
    if (el.hasAttribute('x')) return 'x';
    if (el.hasAttribute('cx')) return 'cx';
    if (el.hasAttribute('x1')) return 'x1';
    return null;
}

designer.prototype.getYname =  function (el){
    if (el.hasAttribute('y')) return 'y';
    if (el.hasAttribute('cy')) return 'cy';
    if (el.hasAttribute('y1')) return 'y1';
    return null;
}

designer.prototype.getWname =  function (el){
    if (el.hasAttribute('width')) return 'width';
    return null;
}

designer.prototype.getHname =  function (el){
    if (el.hasAttribute('width')) return 'width';
    return null;
}



designer.prototype.setElementRect = function(x, y, width, height , el){
    if (el){
        var sel = this.getSourseElement(el);
        if (!sel) return;
        if (x && this.getXname(sel))
            sel.setAttribute( this.getXname(sel), x);
        if (y && this.getYname(sel))
            sel.setAttribute( this.getYname(sel), y); 
        if (width && this.getWname(sel))
            sel.setAttribute( this.getWname(sel) , width);
        if (height  && this.getHname(sel))
            sel.setAttribute( this.getHname(sel), height);
        return;
    }
    if ((this.selectedElemens ) || (this.selectedElemens.length>0)){  
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.setElementRect(x, y, width, height, this.selectedElemens[j]);
        }
  
}


designer.prototype.updateElement = function(el){
    if (el) {
        var select = this.isSelection(el);
        var tel = this.getTransformElement(el.getAttribute('id'));
        var old = el.parentNode.replaceChild(tel ,el);
        this.attach(tel);
        if (select){
            this.repaceselectedElemens(old, tel);
            this.setSelectedClass(tel);
        }
    }
    else{
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.updateElement(this.selectedElemens[j], true);
    }
   
}


designer.prototype.save = function(){
    if (this.sourseDocument){
        libutil.document.writeDoc(this.sourseDocument);
        this.needsave=false;
    }  
}


designer.prototype.deleteElements = function(el){
    if (el){
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
            this.deleteElements(this.selectedElemens[j]);
       
        this.selectedElemens.length=0;
    }   
}

designer.prototype.cloneElements = function(el){
    if (el){
        if (this.sourseDocument){
            var source = this.getSourseElement(el);
            if (source){
                var coneid=this.unicalIdGenerate(source, this.sourseDocument);
                var el_c=source.cloneNode(true);
                el_c.setAttribute('id',  coneid);
                var prnt = source.parentNode;
                prnt.appendChild(el_c);
                this.getTrasformDocument();
                var tel = this.getTransformElement(el_c.getAttribute('id'));
                var prntel = el.parentNode;
                prntel.appendChild(tel);
                this.attach(tel);
                this.changeRect(10,10, null, null, tel);
                this.updateElement(tel);
            }
        }
    }
    else{
        for (var j=0; j< this.selectedElemens.length; ++j)  
            this.cloneElements(this.selectedElemens[j], true);
 
    }   
}

designer.prototype.toFrontElements = function(el){
    if (el){
        if (this.sourseDocument){
            var sel = this.getSourseElement(el);
            if (sel){
                var prnt = sel.parentNode;
                if (prnt.lastElementChild==sel)
                    return;                
                var cel=sel.cloneNode(true);
                prnt.removeChild(sel);
                prnt.appendChild(cel);
            }
        }
    }
    else{
        
        for (var j=0; j< this.selectedElemens.length; ++j)
            this.toFrontElements(this.selectedElemens[j]);
     
        this.clearSelections();

    }   
}

designer.prototype.toBackElements = function(el){
    if (el){
        if (this.sourseDocument){
            var sel = this.getSourseElement(el);
            if (sel){
                var prnt = sel.parentNode;
                if (prnt.firstElementChild==sel)
                    return;                
                var cel=sel.cloneNode(true);
                prnt.removeChild(sel);
                prnt.insertBefore(cel, prnt.firstElementChild);
            }
        }
    }
    else{
        
        for (var j=0; j< this.selectedElemens.length; ++j) 
            this.toBackElements(this.selectedElemens[j]);
        
        this.clearSelections();

    }   
}




// очистка всех выделенных элементов
designer.prototype.clearSelections = function (){
    if (this.selectedElemens!=null){
        for (var i=0;i < this.selectedElemens.length;++i){
            var old = this.selectedElemens[i].oldcomonentclass;
            this.selectedElemens[i].setAttribute('class', old);
        };
    }
    if (event)
        event.stopPropagation();
}



// очистка выделения элемента
designer.prototype.clearSelection = function(el){
    if (this.selectedElemens!=null)
        for (var i=0;i < this.selectedElemens.length;++i)
            if (this.selectedElemens[i]==el){
                var old = this.selectedElemens[i].oldcomonentclass;
                this.selectedElemens[i].setAttribute('class', old ? old : null);
                this.selectedElemens.splice(i,1);
                break;
            }
}

designer.prototype.changeRect = function(x, y, width , height, el){
    if (el){
        this.setElementRect( (x && this.getXname(el) ? parseFloat(this.getAttributeValue(this.getXname(el), el)) + x : x) ,
            (y && this.getYname(el)? parseFloat(this.getAttributeValue(this.getYname(el), el)) + y : y) ,
            (width && this.getWname(el) ? parseFloat(this.getAttributeValue(this.getWname(el), el)) + width : width) ,
            (height && this.getHname(el)? parseFloat(this.getAttributeValue(this.getHname(el), height)) + height : height) , el);
    }
}
 


designer.prototype.isSelection = function(el){
    if (el && this.selectedElemens) {
        for (var j=0; j< this.selectedElemens.length; ++j)
            if (this.selectedElemens[j]==el) return true;
        }
return false;        
}



designer.prototype.repaceselectedElemens = function(old, newel){
    for (var j=0; j< this.selectedElemens.length; ++j){
        if (this.selectedElemens[j]==old){
            this.selectedElemens[j]=newel;
            this.setSelectedClass(newel);
            this.resetSelectedClass(old);            
        }
    }
    return false;
}
 
designer.prototype.setSelectedClass = function(el){
    el.oldcomonentclass= el.oldcomonentclass ?
    el.getAttribute('class') : null;
    el.setAttribute('class', (el.oldcomonentclass) ? 
        el.oldcomonentclass + " designer_selected" : "designer_selected");
}

designer.prototype.resetSelectedClass = function(el){
    if (el.oldcomonentclass)
        el.setAttribute('class',el.oldcomonentclass);
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

designer.prototype.click_component = function(){
    var el= this.getTarget(event);
    designutil.toolwin.setCurrentRedactor(window);
    this.select_component(el, event.shiftKey, event.ctrlKey);
    event.stopPropagation();
}

designer.prototype.click_parented = function(ev){
if (ev && ev.clientX.toString() && ev.clientY.toString())
       this.createLibComponent(ev.clientX.toString(), ev.clientY.toString());
}

designer.prototype.createLibComponent = function(x, y){
    var created = designutil.toolwin.getSelectedComponent();
    if (created && x && y){
         var coneid=this.unicalIdGenerate(created , this.sourseDocument);
         var prnt = this.sourseDocument.documentElement;         
         var el =prnt.appendChild(created.cloneNode(true)); 
         el.setAttribute('id',  coneid);
         if (el.hasAttribute(this.getXname(el))) el.setAttribute(this.getXname(el), x);
         if (el.hasAttribute(this.getYname(el))) el.setAttribute(this.getYname(el), y);
         this.getTrasformDocument();
         var tel = this.getTransformElement(coneid);
         this.instantdocument.documentElement.appendChild(tel);
         this.attach(tel);
         this.updateElement(tel);
         this.setNeedSave(); }     
}

/*выделение элемента*/
designer.prototype.select_component = function(el, shift, ctnrl){
    if (this.selectedElemens==null){
        this.selectedElemens = new Array();
    }
    
    var el_class = el.getAttribute('class');
    if (el_class=="designer_selected"){
        if (shift){
            clearSelection(el);
        }
        return false;
    }

    if (!shift){
        this.clearSelections();
        this.selectedElemens.length=0;
        this.selectedElemens.push(el);
        this.setSelectedClass(el);
        this.show_property(el);

    }
    else{
        var finded=false;
        for (var i=0;i < this.selectedElemens.length;++i){
            if (this.selectedElemens[i]==el){
                finded=true;
                break;
            }
        }
        if (!finded){
            this.selectedElemens.push(el);
            this.setSelectedClass(el);
            this.show_property(el);
        }
    }
}


/*обработчик событий клавиатуры*/
designer.prototype.keybord_dispatcher = function (){
    
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
    
    var ismove=false;

    for (var i=0;i < this.selectedElemens.length;++i){
        var el=this.selectedElemens[i];
        if (event.ctrlKey) {
            switch (event.keyIdentifier){
                case 'Left':{
                    if (el.hasAttribute('x')){   
                    this.setAttributeValue( 'x', parseFloat(this.getAttributeValue('x', el)) - incr, el);
                    ismove=true;}
                    break;
                }
                case 'Right':{
                    if (el.hasAttribute('x')){     
                    this.setAttributeValue('x', parseFloat(this.getAttributeValue('x', el)) + incr, el);
                    ismove=true;}
                    break;
                }     
                case 'Up':{
                    if (el.hasAttribute('y')){     
                    this.setAttributeValue('y', parseFloat(this.getAttributeValue('y', el)) - incr, el);
                    ismove=true;}
                    break;
                }
                case 'Down':{
                    if (el.hasAttribute('y')){     
                    this.setAttributeValue( 'y', parseFloat(this.getAttributeValue('y', el)) + incr, el);
                    ismove=true;}
                    break
                }
            }                
        }
        if (event.shiftKey){
            switch (event.keyIdentifier){        
                case 'Left':{
                    this.setAttributeValue('width', parseFloat(this.getAttributeValue('width', el)) - incr , el);
                    ismove=true;
                    break;
                }
                case 'Right':{
                    this.setAttributeValue('width', parseFloat(this.getAttributeValue('width',el)) + incr, el);
                    ismove=true;
                    break;
                }     
                case 'Up':{
                    this.setAttributeValue('height', parseFloat(this.getAttributeValue('width',el)) - incr, el);
                    ismove=true;
                    break;
                }
                case 'Down':{
                    this.setAttributeValue('height', parseFloat(this.getAttributeValue('width',el)) + incr, el);
                    ismove=true;
                    break
                }
            }            
        }

    }
    
    if (ismove){
        this.updateElement();

        }   
}



designer.prototype.mousemove_document = function (){
    if ((this.objins_draggedstart) && (this.dragstartevent)){
        if (this.mousmoveevent){
            var xsh=event.clientX-this.mousmoveevent.clientX;
            var ysh=event.clientY-this.mousmoveevent.clientY
        }
        if (this.inspectorFrame){
            if (this.mousmoveevent){
        }
        }
    }
    this.mousmoveevent=event;
}


designer.prototype.mousedown_document = function (){
    if ((event.button==0) && (!event.shiftKey)){
        var trgt = this.getTarget(event)
        if (this.selectedElemens){
            if (this.selectedElemens.length>0){
                for (var i=0; i<this.selectedElemens.length;++i){ 
                    if (trgt==this.selectedElemens[i]){
                        this.dragstartevent = event;
                        return;
                    }
                }
            }
        }
    }
    this.draggedstart=undefined;
    this.dragstartevent = undefined;
    this.objins_draggedstart=undefined;
    this.mousmoveevent=undefined;
}




designer.prototype.mousedown_component = function (){
    if ((event.button==0)){
        var trgt = this.getTarget(event)
        var cls = trgt.getAttribute('class');
        if ((cls) && (cls.search('designer_selected')!=-1)){
            this.draggedstart=true;
            this.objins_draggedstart=undefined;
            return;
        }
    }
    this.draggedstart=undefined;
}


designer.prototype.mouseup_document = function (){
    if (event.button==0){
        if (this.dragstartevent){
            var xsh=event.clientX-this.dragstartevent.clientX;
            var ysh=event.clientY-this.dragstartevent.clientY;
            if (this.draggedstart){
                if (this.selectedElemens) {
                    for (var i=0;i < this.selectedElemens.length;++i){
                        var el = this.selectedElemens[i];
                        this.changeRect( xsh, ysh , null, null,  el);
                    }
                    this.updateElement();
                    this.setNeedSave();
                }
                this.show_property();
            }
            else{
                if ((this.objins_draggedstart)){           
                    if (this.inspectorFrame){
                        var x = parseInt(this.inspectorFrame.getAttribute('x')) + xsh;
                        var y = parseInt(this.inspectorFrame.getAttribute('y')) + ysh;
                        var width = parseInt(this.inspectorFrame.getAttribute('width'));
                        var height = parseInt(this.inspectorFrame.getAttribute('height'));

                    }
            
                }
            }
        }
    }
    this.draggedstart=undefined;
    this.dragstartevent = undefined;
    this.objins_draggedstart=undefined;
    this.mousmoveevent=undefined;

}

designer.prototype.contextmenue = function (){
    this.createContextMenu(event);
    event.stopPropagation();
    event.preventDefault();    
}



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


    var l= event.clientX;
    var t= event.clientY;
    
    var el = event.target;
    var isRoot=(el==this.instantdocument.documentElement);
    if (isRoot) return;

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

}




designer.prototype.ContextMenuComponent = function(tbody){
    
    this.ContextMenuButton(tbody, 'Bring to Front', true,
        function(){
            document.red.toFrontElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
        } );
        
    this.ContextMenuButton(tbody, 'Send to Back', true,
        function(){
            document.red.toBackElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
        } );  
        
    this.ContextMenuButton(tbody, 'Delete', true,
        function(){
            document.red.deleteElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
        } );  
 
    this.ContextMenuButton(tbody, 'Clone', true,
        function(){
            document.red.cloneElements();
            document.red.ContextMenuDestroy();
            document.red.setNeedSave();
        } ); 
        
    this.ContextMenuButton(tbody, 'Close', true,
        function(){
            document.red.ContextMenuDestroy();
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


    this.inspectorFrame=designutil.toolwin.getObjectInspector();
    if (!this.inspectorFrame) return;
    this.inspectortbody=designutil.toolwin.getObjectInspectorTbody();
    
    libutil.dom.clearChildNode(this.inspectortbody);   

    var trh= libutil.html.create_tr(this.inspectortbody);

            
    var th1= libutil.html.create_th(trh);
    //th1.setAttribute('width','50%');
    th1.innerHTML='Attribute';
            
    var th2= libutil.html.create_th(trh);
    th2.setAttribute('width','80%');
    th2.innerHTML='Value';

                            
    for (var i=0; i<attriblist.length; ++i ){
        
        var tr= libutil.html.create_tr(this.inspectortbody);
       
        var td1= libutil.html.create_td(tr);
        td1.innerHTML=attriblist[i]['name'];
        
        td1.className='static';
   
        var td2= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var val=this.getAttributeValue(attriblist[i]['name']);
        td2.innerHTML= val ? val : "";
        
        if (val==undefined)
            td2.className='diffvalue';
        
        td2.type=(!attriblist[i]['type']) ? 0 : (attriblist[i]['type']['type'] ? attriblist[i]['type']['type'] : 0) ;
        td2.regex=(!attriblist[i]['type']) ? null : (attriblist[i]['type']['regex'] ? attriblist[i]['type']['type'] : null) ;
        td2.list=(!attriblist[i]['type']) ? null : (attriblist[i]['type']['list'] ? attriblist[i]['type']['list'] : null) ;
        ;
        td2.onclick=function(ev) {
            if (document.red) document.red.property_row_focus(ev);
        }
        td2.prop_dvn=attriblist[i];


    }
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
            var retval = designutil.toolwin.propertydialog(td['name'], value);
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
                libutil.html.create_input(td, 'text', value);
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
    
    el.onblur= function(ev) {
        if (document.red) document.red.property_leave_focus(ev);
    }
    el.addEventListener( 'keyup' ,function (ev) {       
        if ((ev.keyIdentifier=="Enter"))
            document.red.property_leave_focus(ev);
        else 
            event.stopPropagation();
    });    
}


designer.prototype.property_leave_focus = function(event){
    var oldval=event.target.oldval;
    var value =event.target.value;
    var td=event.target.parentNode;
    td.removeChild(event.target);
    td.innerHTML=value;
    if (oldval!=value){
        this.setProperty(td.prop_dvn,value);
    }
    event.preventDefault();
    event.stopPropagation();   
}


designer.prototype.setNeedSave = function(){
    this.needsave=true; 
    designutil.toolwin.setMainWindowToolStatus(1);
}



    



///




////





designutil.componentinfo.prototype.init = function(libsulr){
    this.libsdoc=libutil.document.readDoc(libsulr);
    if (this.libsdoc){
        var els=this.libsdoc.getElementsByTagName('include');
        for (var i=0; i<els.length;++i)
            if (els[i].getAttribute('xsi:schemaLocation')) 
                this.libs.push(els[i].getAttribute('xsi:schemaLocation'));

        if (this.libs.length>0)
            for (var i=0; i<this.libs.length;++i)
                this.initlibs(this.libs[i]);   
    }
}

designutil.componentinfo.prototype.initlibs = function(libulr){
    var libdoc=libutil.document.readDoc(libulr);
    if (libdoc){ 
        this.read_types(libdoc);
        this.read_elements(libdoc);
        this.read_creators(libdoc);
    }
}




designutil.componentinfo.prototype.getAttributeList = function (el){ 
    
    var node = el['nodeName'];
    if ((node) && (this.elements[node]!=undefined))
        return this.elements[node];

    this.attributes_for_nullschema(el);
    return this.elements[node];

    
}


designutil.componentinfo.prototype.attributes_for_nullschema = function (el){ 
    var node = el['nodeName'];

    var result =[];
    for (var i=0; i< el.attributes.length; ++i){
        result.push({
            'name' : el.attributes[i].name , 
            'type' : null, 
            'use' : null, 
            'default' : null
        })
                
        this.elements[node] = {
            'name' : els[i].getAttribute('name'),
            'type' : els[i].getAttribute('type'),
            'attributes' : result
        };
   
    }
}

designutil.componentinfo.prototype.read_types =  function(doc){
    if (doc){
        var docElement=doc.documentElement;
        var els=doc.getElementsByTagName('simpleType');
        for (var i=0; i<els.length;++i){
            if ((els[i].parentNode==docElement) && (els[i].getAttribute('name'))){
                var info=this.read_simple_type(els[i]);
                var nm = els[i].getAttribute('name');
                if (info)
                    this.types[nm] = {
                        'name' : nm , 
                        'type' : info.type, 
                        'base' : info['base'], 
                        'regex' : info['regex'],  
                        'list' : info['list']
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

designutil.componentinfo.prototype.read_simple_type =  function(el){
    if (el){
        var restrictel=el.firstElementChild;
        if ((restrictel) || (restrictel.localName=='restriction')){
            return this.read_restriction_type(restrictel);
        }
    }
    return {
        'type': 0, 
        'base': null, 
        'regex': null, 
        'list': null
    };
}

designutil.componentinfo.prototype.read_restriction_type =  function(el){
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
            
            
     

designutil.componentinfo.prototype.read_elements =  function(doc){
    if (doc){
        var els=doc.getElementsByTagName('element');
        for (var i=0; i<els.length;++i){
            if (els[i].getAttribute('name')){
                this.elements[els[i].getAttribute('name')]={
                    'name' : els[i].getAttribute('name'),
                    'type' : els[i].getAttribute('type'),
                    'attributes' : null
                };
                this.read_attributes(els[i],this.elements[els[i].getAttribute('name')]);
            }
        }
    }
}

designutil.componentinfo.prototype.read_attributes = function(el,  info){
    var result = new Object();
    if (!el)
        return result;
    var typeel=el.firstElementChild;
    if ((!typeel) || (typeel.localName!='complexType'))
        return result; 
    if (!typeel) return;
        
    for (var ch=typeel.firstElementChild; ch; ch=ch.nextElementSibling)
        if ((ch.localName=='attribute') && (ch.getAttribute('name')))
            result[ch.getAttribute('name')] = {
                'name' : ch.getAttribute('name') , 
                'type' : this.get_attribute(ch.getAttribute('type')), 
                'use' : ch.getAttribute('use'), 
                'default' : ch.getAttribute('default')
            };
                
    info.attributes=result;
}

designutil.componentinfo.prototype.get_attribute = function(name){
    return ( name && this.types[name]) ? (this.types[name]) : null;
}


designutil.componentinfo.prototype.read_creators =  function(doc){
    if (doc){
        var els=doc.getElementsByTagName('creator');
        for (var i=0; i<els.length;++i)
            if (els[i].nodeName=='dvnlib:creator'){
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


            
 ///




////               
                
                
designutil.toolwin.getMainWindow = function (){
    libutil.www.create_tbwindow('maintool', 'Редактор' ,'100' , '100', '600','64','yes','yes',null,null,
        ['save','objinsp', 'forminsp','libinsp', 'exit'],
        ['Сохранить','Редактор свойств', 'Редактор форм','Панель компонентов', 'Выход'],
        [function() {
            designutil.toolwin.SaveAll();
        },
        function() {
            designutil.toolwin.resetObjectInspector();
        },
        function() {
            designutil.toolwin.resetFormInspector();
        },
        function() {
            designutil.toolwin.resetLibInspector();
        },           
        function() {
            designutil.toolwin.destroyMainWindow();
        }],
        designutil.toolwin.destroyMainWindow);
        
        
    var tmp=libutil.global.getGlobal();
    
        
    tmp.maintool.onload =  function() {
            //setTimeout( function() {
            //libutil.www.correct_window_height(tmp.maintool,30);}, 1000);
        }  
    
    
     
    designutil.toolwin.setMainWindowToolStatus();
    tmp.maintool.focus();
    
}




designutil.toolwin.setMainWindowToolStatus = function (val){ 
    if ((val==1 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'save', designutil.toolwin.isNeedSave() ?  'on' :  'disabled');
    if ((val==2 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'objinsp', designutil.toolwin.getObjectInspector() ?  'off' :  'on');
    if ((val==3 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'forminsp', designutil.toolwin.getFormInspector() ?  'off' :  'on');
    if ((val==4 || !val)) 
        libutil.www.set_tbwindow_btnstatus('maintool', null, 'libinsp', designutil.toolwin.getLibInspector() ?  'off' :  'on');
}


designutil.toolwin.destroyMainWindow = function(){
        var tmp=libutil.global.getGlobal();
        if (tmp && tmp.maintool)
            tmp.maintool=undefined;
        if (!designutil.toolwin.isNeedSave()){          
            dvnci_exit();
            return;}
        if (confirm("Выйти без сохранения?")){
            dvnci_exit();
            return;
        } 
        else{
        setTimeout(function() {
            designutil.toolwin.getMainWindow();
        }, 10);}
}


///  Object inspector

designutil.toolwin.getObjectInspector = function (force){
    var tmp=libutil.global.getGlobal();
    if (!force && !tmp.objectinspectorwin) return null;
    if (tmp && !tmp.objectinspectorwin){
        var objectinspectorwin=libutil.window.createhtml('_ObjectInspector','Свойства','100', '900', '400','650','yes','yes',null,null, "../util/css/objectinspector.css");
        tmp.objectinspectorwin=objectinspectorwin;
        tmp.objectinspectordoc=objectinspectorwin.document;
        objectinspectorwin.onunload=designutil.toolwin.destroyObjectInspector;
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
        var current=designutil.toolwin.getCurrentRedactor();
        if (current)
            current.show_property();
              
    }   
    return (tmp && tmp.objectinspectorwin) ? tmp.objectinspectorwin : null;
}

designutil.toolwin.resetObjectInspector = function(){
    var vis =  designutil.toolwin.getObjectInspector();
    var tmp=libutil.global.getGlobal();
    if (vis && tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
    else
        designutil.toolwin.getObjectInspector(true);
    designutil.toolwin.setMainWindowToolStatus(2);
        
} 

designutil.toolwin.getObjectInspectorDocument = function(){
    var tmp = libutil.global.getGlobal();
    if (tmp && tmp.objectinspectordoc) {
        return tmp.objectinspectordoc; 
    }
}

designutil.toolwin.getObjectInspectorTbody = function(){
    var tmp = libutil.global.getGlobal();
    if (tmp && tmp.objectinspectortbody) {
        return tmp.objectinspectortbody;       
    }   
}  


designutil.toolwin.showObjectInspector = function(){
    var tmp = designutil.toolwin.getObjectInspector();
    if (tmp)
        tmp.focus();
}



designutil.toolwin.closeObjectInspector = function(){
    var tmp = designutil.toolwin.getObjectInspector();
    if (tmp.objectinspectorwin)
        tmp.objectinspectorwin.close();
}

designutil.toolwin.destroyObjectInspector = function(){
    var tmp=libutil.global.getGlobal();
    if (tmp && tmp.objectinspectorwin)
        tmp.objectinspectorwin=undefined;
    if (tmp && tmp.objectinspectordoc)
        tmp.objectinspectordoc=undefined;
    if (tmp && tmp.objectinspectortbody)
        tmp.objectinspectortbody=undefined;
    designutil.toolwin.setMainWindowToolStatus(2);
    
}


// Form inspector


designutil.toolwin.getFormInspector = function (force){
    var tmp=libutil.global.getGlobal();
    if (!tmp.formtool && !force) return null;
    if (tmp && !tmp.formtool){

        libutil.www.create_tbwindow('formtool', 'Окна' ,'600','100', '600','200','yes','yes',null,null,
            ['add', 'new'],
            ['Добавить из файла','Новая форма'],
            [
            function() {
                designutil.toolwin.addwindowfromfile();             
            },
            function() {
                designutil.toolwin.addnewwindow();
            }]);
    
        var objdoc =tmp.formtool.document;
        tmp.formtool.onunload=designutil.toolwin.destroyFormInspector;

        var body=objdoc.getElementsByTagName('body')[0];
        var head=objdoc.getElementsByTagName('head')[0];
        libutil.html.create_link(head, 'stylesheet', 'text/css',"../util/css/forminspector.css");
        var div = libutil.html.create_div(libutil.html.create_div(body),null,"scrollWrapper");
        var table = libutil.html.create_table(div,null,"scrollable");
        var tbody = libutil.html.create_tbody(table);
        libutil.html.create_tr(tbody);
        tmp.formtooltbody=tbody;
    }
 
    designutil.toolwin.fillFormInspector();
    return (tmp && tmp.formtool) ? tmp.formtool : null;
}

designutil.toolwin.resetFormInspector = function(){
    var vis =  designutil.toolwin.getFormInspector();
    var tmp=libutil.global.getGlobal();
    if (vis && tmp.formtool)
        tmp.formtool.close();
    else
        designutil.toolwin.getFormInspector(true);
    var tmp=libutil.global.getGlobal();
    tmp.formtool.focus();
    designutil.toolwin.setMainWindowToolStatus(3);
        
} 

designutil.toolwin.fillFormInspector = function (){
    var tmp=libutil.global.getGlobal();
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
   
        designutil.toolwin.fiCreateRow(tr,fl[i],'name');
        designutil.toolwin.fiCreateRow(tr,fl[i],'caption');
        designutil.toolwin.fiCreateRow(tr,fl[i],'left', '50px');       
        designutil.toolwin.fiCreateRow(tr,fl[i],'top', '50px');
        designutil.toolwin.fiCreateRow(tr,fl[i],'width', '50px');       
        designutil.toolwin.fiCreateRow(tr,fl[i],'height', '50px'); 
        designutil.toolwin.fiCreateRow(tr,fl[i],'visible', '50px'/*, ['','true','false']*/);
        designutil.toolwin.fiCreateRow(tr,fl[i],'allwaystop', '50px'/*,, ['','true']*/);       
        designutil.toolwin.fiCreateRow(tr,fl[i],'resizable', '50px'/*,, ['','true']*/);
        designutil.toolwin.fiCreateRow(tr,fl[i],'decorated', '50px'/*,, ['','no']*/);
        designutil.toolwin.fiCreateRow(tr,fl[i],'modal', '50px'/*,, ['','true']*/);        
        
        var td11= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btno = libutil.html.create_button( td11,'height: 15px;',null,'');
        btno.setAttribute('onclick','designutil.toolwin.resetwindow("'+formname+ '");');
 
        
        var td13= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
        var btnd = libutil.html.create_button( td13,'height: 15px;',null,'');
        btnd.setAttribute('onclick','designutil.toolwin.removeFormFromProject("'+formname+ '");');
    
    }
}

designutil.toolwin.fiCreateRow = function(tr, tblrow, name, width, lst){
    var td= libutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0;' + width ? 'width: ' + width + ';' : '');
    var tmp= tblrow[name] ? tblrow[name] : '';
    if (lst)
        td.lst=lst; 
    td.innerHTML= tmp;
    td.elem=tblrow;
    td.value=tmp;
    td.propname=name;
    td.onclick=function(ev) {
        designutil.toolwin.fiPropertyRowFocus(ev);    
    }
}



designutil.toolwin.fiPropertyRowFocus = function(ev){
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
            designutil.toolwin.fiPropertyLeaveFocus(ev);
        }

        edit.addEventListener( 'keyup' ,function (ev) {       
            if ((ev.keyIdentifier=="Enter"))
                designutil.toolwin.fiPropertyLeaveFocus(ev);
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

designutil.toolwin.fiPropertyLeaveFocus = function(event){

    if (!event.target) return;
    var oldval=event.target.oldval;
    var value =event.target.value;
    var td=event.target.parentNode;
    td.removeChild(event.target);
    td.innerHTML=value;
    if ((oldval!=value) && (designutil.toolwin.fiCheckFormParam(td.propname,value))){  
        
        
        if (td.elem && td.elem['element']){     
            
            td.elem['element'].setAttribute(td.propname,value);
            td.elem[td.propname]=value;
            designutil.toolwin.closewindow(td.elem['name'], true);
            td.elem['param'] = libutil.project.buildparam(td.elem['element']);
            designutil.toolwin.openwindow(td.elem['name']);

            
        }
        var fdoc = libutil.global.getStartupDoc();
        fdoc.needsave=true;
        designutil.toolwin.setMainWindowToolStatus();

    }

          
    event.preventDefault();
    event.stopPropagation();   
}

 

designutil.toolwin.fiCheckFormParam = function(name, val){
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



designutil.toolwin.destroyFormInspector = function(){
    var tmp=libutil.global.getGlobal();
    if (tmp && tmp.formtool)
        tmp.formtool=undefined;
    if (tmp && tmp.formtooltbody)
        tmp.formtooltbody=undefined; 
    designutil.toolwin.setMainWindowToolStatus(3);  
}

//


designutil.toolwin.getLibInspector = function (force){    
    var tmp=libutil.global.getGlobal();
    if (tmp && !tmp.libtool && !force) return null;
    if (!tmp.libtool){
        var libs =libutil.global.getLibList();
        
        var heigth = libs.length>0 ? 86 + 52 * (libs.length-1) : 46;
        
        libutil.www.create_tbwindow('libtool','Библиотека','300','100', '600',heigth,'yes','yes',null,null);
        tmp.libtool.onunload=designutil.toolwin.destroyLibInspector;
    
        var libs =libutil.global.getLibList();
        for (var i=0; i<libs.length;++i){
            var lib =libs[i];
            var btnsname =[];
            var btnsfunc =[];
            var btnshint =[];
            var comps =lib.components;        
            for (var j=0; j<comps.length;++j){
                btnsname.push(comps[j].hint);
                btnsfunc.push(designutil.toolwin.setSelectedToolEvent);
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



designutil.toolwin.resetLibInspector = function(){
    
    var tmp=libutil.global.getGlobal();
    if (tmp.libtool)
        tmp.libtool.close();
    else
        designutil.toolwin.getLibInspector(true);
    var tmp=libutil.global.getGlobal();
    tmp.libtool.focus();
    designutil.toolwin.setMainWindowToolStatus(4);     
} 

designutil.toolwin.setSelectedToolEvent = function(event){
    if (event && event.target && event.target.parentNode){
        var trgt=event.target.parentNode;
        designutil.toolwin.setSelectedComponent(trgt.nametool, trgt.namebtn);
    }
}

designutil.toolwin.setSelectedComponent = function(tool, comp){
    //alert(tool + ' : ' + comp);
    var tmp= libutil.global.getGlobal(); 
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


designutil.toolwin.getSelectedComponent = function(){
    var tmp = designutil.toolwin.setSelectedComponent();
    return (tmp && tmp.tool && tmp.component)? libutil.project.get_components(tmp.tool, tmp.component): null;
}


designutil.toolwin.destroyLibInspector = function(){
    var tmp=libutil.global.getGlobal();
    if (tmp && tmp.libtool)
        tmp.libtool=undefined;
    designutil.toolwin.setMainWindowToolStatus(4);  
}



//

designutil.toolwin.openwindow = function(name){
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


designutil.toolwin.closewindow = function (name){
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

designutil.toolwin.resetwindow = function (name){
    var fl =  libutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i){
            try{
                if (fl[i]['name']==name){
                    if (fl[i].window)
                        designutil.toolwin.closewindow(name);
                    else
                        designutil.toolwin.openwindow(name);              
                }
            }
            catch(error){
                alert(error);
            }
        }
    }
}

designutil.toolwin.windowstatus = function (name){
    var fl =  libutil.global.getFormList(); 
    if (fl){  
        for (var i=0; i<fl.length;++i)
            if (fl[i]['name']==name)
                return fl[i].window ? true : false;
        }
    return false;
}

designutil.toolwin.SaveAll = function(){ 
    var fl= libutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red){
            fl[i].red.save();
        }   
    }
    var fdoc = libutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) {
        libutil.document.writeDoc(fdoc);
        fdoc = libutil.global.getStartupDoc();
        fdoc.needsave=undefined;
    }    
    designutil.toolwin.setMainWindowToolStatus();
}

designutil.toolwin.isNeedSave = function (){
    var fl= libutil.global.getFormList();
    for (var i=0; i<fl.length; ++i ){
        if (fl[i].red && fl[i].red.needsave)
            return true;        
    }   
    var fdoc = libutil.global.getStartupDoc();
    if (fdoc && fdoc.needsave) return true;
    return false;
}

designutil.toolwin.setCurrentRedactor = function (win){
    var tmp= libutil.global.getGlobal();
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

designutil.toolwin.getCurrentRedactor = function (){
    var tmp= libutil.global.getGlobal();
    return tmp.currentred;
}

designutil.toolwin.findwindow = function (name){
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

designutil.toolwin.windowexists = function (name){
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



designutil.toolwin.addwindowfromfile = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return; 
    var openddoc = libutil.document.readDoc(openfile);
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
    if (designutil.toolwin.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    designutil.toolwin.addform(openfile,openform); 
}
               
designutil.toolwin.addnewwindow = function (){
    var openfile= prompt('Введите имя файла','');
    if (!openfile || openfile=='') return;          
    if (!libutil.regex.check(openfile,'[A-Za-z][A-Za-z0-9]*\\.(xml|html|htm)')){
        alert('Имя формы '+openfile+' некорректно!');
        return;
    }
               
    var openddoc = libutil.document.readDoc(openfile);
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
    if (designutil.toolwin.windowexists(openform)){
        alert('Форма с именем '+openform+' уже существует!');
        return;
    }
    designutil.toolwin.createfileform(openfile);
    designutil.toolwin.addform(openfile,openform);
           
}

designutil.toolwin.addform = function(file, name){
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
        designutil.toolwin.fillFormInspector();
        var fdoc = libutil.global.getStartupDoc();
        if (fdoc && !fdoc.needsave) fdoc.needsave=true;
        designutil.toolwin.setMainWindowToolStatus();
    }
    catch(error){
        alert(error);
    }
       
}

designutil.toolwin.createfileform = function(file){
    var tmp=libutil.global.getGlobal();
    var prjpath=tmp.projectPath;
    var txt = '<?xml-stylesheet href="../util/lib.xsl" type="text/xsl"?>\n'+
    '<svg xmlns="http://www.w3.org/2000/svg" xmlns:mlib="http://dvnci/mlib" xmlns:xlink="http://www.w3.org/1999/xlink" width="100%" height="100%" version="1.1" style="" onload="libutil.startup.init()">\n'+
    '\n'+
    '</svg>\n';
    return dvnci_writefile(prjpath.toString()+file,txt);      
}


designutil.toolwin.removeFormFromProject =function(name){
    if (confirm('Удалить форму "'+name+'" из проекта?')){
        try{
            var fl =  libutil.global.getFormList();
            if (fl){  
                for (var i=0; i<fl.length;++i){
                    if (fl[i]['name']==name){
                        designutil.toolwin.closewindow(name);
                        libutil.util.remove_element_arr(fl,i);               
                        var fdoc = libutil.global.getStartupDoc();
                        var projel=fdoc.getElementsByTagName('project')[0];
                        var els=fdoc.getElementsByTagName('form');
                
                        for (var j=0; j<els.length;++j){
                            if (els[j].getAttribute('name')==name){
                                els[j].parentNode.removeChild(els[j]);
                                designutil.toolwin.fillFormInspector();
                                if (fdoc && !fdoc.needsave) fdoc.needsave=true;
                                designutil.toolwin.setMainWindowToolStatus();
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

designutil.toolwin.propertydialog = function(name, value){
    return libutil.window.create_modal('../util/html/propertydialog.html',name , value, '20%', '20%', '60%', '60%', '1', 'yes');       
}                
                
                
                
                
  
        
                        
