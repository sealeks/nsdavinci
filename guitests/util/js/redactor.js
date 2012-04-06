
///

function schema_info(){
    this.elements = new Object();
    this.types = new Object();
    this.libs = [];
    this.creators = new Object();;
}


schema_info.prototype.init = function(libsulr){
    this.libsdoc=mainlibutil.document.readDoc(libsulr);
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

schema_info.prototype.initlibs = function(libulr){
    var libdoc=mainlibutil.document.readDoc(libulr);
    if (libdoc){ 
        this.read_types(libdoc);
        this.read_elements(libdoc);
        this.read_creators(libdoc);
    }
}




schema_info.prototype.getAttributeList = function (el){ 
    
    var node = el['nodeName'];
    if ((node) && (this.elements[node]!=undefined))
        return this.elements[node];

    this.attributes_for_nullschema(el);
    return this.elements[node];

    
}


schema_info.prototype.attributes_for_nullschema = function (el){ 
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

schema_info.prototype.read_types =  function(doc){
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

schema_info.prototype.read_simple_type =  function(el){
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

schema_info.prototype.read_restriction_type =  function(el){
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
            
            
     

schema_info.prototype.read_elements =  function(doc){
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

schema_info.prototype.read_attributes = function(el,  info){
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

schema_info.prototype.get_attribute = function(name){
    return ( name && this.types[name]) ? (this.types[name]) : null;
}


schema_info.prototype.read_creators =  function(doc){
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

function redactor(doc){ 
    this.instantdocument=doc;
    this.schema=new schema_info();
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
redactor.prototype.attach = function(el){
    try{
        if (el==this.instantdocument.documentElement){
            el.oldoncick = el.oncick;
            el.onclick = function(ev) {
                if (document.red){
                    document.red.clearSelections();
                    document.red.click_parented(ev);
                    mainlibutil.designtime.setCurrentRedactor(window);
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
redactor.prototype.getSourseDocument = function (){ 
    if (this.sourseDocument)
        return this.sourseDocument;
    try{
        this.sourseDocument = mainlibutil.document.readDoc(this.instantdocument.URL);
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



redactor.prototype.getLightDocument = function (){ 
    try{
        this.lightDocument = mainlibutil.document.readDoc(this.instantdocument.URL);
        
    }
    catch(except){
        this.lightDocument = null;
    }
    return this.lightDocument;   
}


redactor.prototype.getLightElement = function (el){
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
redactor.prototype.readXsltDocument = function(data){
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
                this.soursexslt = mainlibutil.document.readDoc(urlxslt);
                this.xsltProcessor=new XSLTProcessor();  
                this.xsltProcessor.importStylesheet(this.soursexslt); 
                this.trasformsourse = this.xsltProcessor.transformToDocument(this.sourseDocument);
                return;
            }
    } 
    this.xslturl=undefined;
}

redactor.prototype.getTrasformDocument = function(){
    if (this.xsltProcessor && this.soursexslt)
        return this.trasformsourse = this.xsltProcessor.transformToDocument(this.sourseDocument);
    return undefined;
}



redactor.prototype.getSourseElement = function(el){
    return el && el.id && this.sourseDocument ? 
        this.sourseDocument.getElementById(el.id) : null;
}


redactor.prototype.getTransformElement = function(elid){
    if (this.trasformsourse) {
        var el=this.sourseDocument.getElementById(elid);
        if (el){
            el=el.cloneNode(true);
            return this.getLightElement(el);
        }
    }
return null;
}





redactor.prototype.getTarget = function (ev){
  
    var el = ev.target.correspondingUseElement ? ev.target.correspondingUseElement : ev.target;
    
    var owndoc = el.ownerDocument;
    
    while ((el!=owndoc) && (!el.getAttribute('id')) && (el.parentNode))
        el=el.parentNode;

    return ((el==owndoc)) || (!el.getAttribute('id')) ? undefined : el;
}

redactor.prototype.check_is_parent = function (el, self){
    var tst=el;
    if ((!tst) || (tst===this.instantdocument.documentElement)) return false;
    while (tst.parentNode!==this.instantdocument.documentElement){
        if (tst.parentNode==self)
            return true;
        tst=tst.parentNode;
    }
    return false;
}



redactor.prototype.unicalIdGenerate = function(el, doc) {
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


redactor.prototype.getAttributeList = function(el) {
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



redactor.prototype.getAttributeValue = function(name, el){
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




redactor.prototype.setAttributeValue = function(name, val, el){
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


redactor.prototype.setProperty = function(nm, val){
    this.setAttributeValue(nm['name'],val);
    this.updateElement();
    this.setNeedSave();
    mainlibutil.designtime.setMainWindowToolStatus(1);
    this.show_property();
    
    
}    


redactor.prototype.getXname =  function (el){
    if (el.hasAttribute('x')) return 'x';
    if (el.hasAttribute('cx')) return 'cx';
    if (el.hasAttribute('x1')) return 'x1';
    return null;
}

redactor.prototype.getYname =  function (el){
    if (el.hasAttribute('y')) return 'y';
    if (el.hasAttribute('cy')) return 'cy';
    if (el.hasAttribute('y1')) return 'y1';
    return null;
}

redactor.prototype.getWname =  function (el){
    if (el.hasAttribute('width')) return 'width';
    return null;
}

redactor.prototype.getHname =  function (el){
    if (el.hasAttribute('width')) return 'width';
    return null;
}



redactor.prototype.setElementRect = function(x, y, width, height , el){
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


redactor.prototype.updateElement = function(el){
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


redactor.prototype.save = function(){
    if (this.sourseDocument){
        mainlibutil.document.writeDoc(this.sourseDocument);
        this.needsave=false;
    }  
}


redactor.prototype.deleteElements = function(el){
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

redactor.prototype.cloneElements = function(el){
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

redactor.prototype.toFrontElements = function(el){
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

redactor.prototype.toBackElements = function(el){
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
redactor.prototype.clearSelections = function (){
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
redactor.prototype.clearSelection = function(el){
    if (this.selectedElemens!=null)
        for (var i=0;i < this.selectedElemens.length;++i)
            if (this.selectedElemens[i]==el){
                var old = this.selectedElemens[i].oldcomonentclass;
                this.selectedElemens[i].setAttribute('class', old ? old : null);
                this.selectedElemens.splice(i,1);
                break;
            }
}

redactor.prototype.changeRect = function(x, y, width , height, el){
    if (el){
        this.setElementRect( (x && this.getXname(el) ? parseFloat(this.getAttributeValue(this.getXname(el), el)) + x : x) ,
            (y && this.getYname(el)? parseFloat(this.getAttributeValue(this.getYname(el), el)) + y : y) ,
            (width && this.getWname(el) ? parseFloat(this.getAttributeValue(this.getWname(el), el)) + width : width) ,
            (height && this.getHname(el)? parseFloat(this.getAttributeValue(this.getHname(el), height)) + height : height) , el);
    }
}
 


redactor.prototype.isSelection = function(el){
    if (el && this.selectedElemens) {
        for (var j=0; j< this.selectedElemens.length; ++j)
            if (this.selectedElemens[j]==el) return true;
        }
return false;        
}



redactor.prototype.repaceselectedElemens = function(old, newel){
    for (var j=0; j< this.selectedElemens.length; ++j){
        if (this.selectedElemens[j]==old){
            this.selectedElemens[j]=newel;
            this.setSelectedClass(newel);
            this.resetSelectedClass(old);            
        }
    }
    return false;
}
 
redactor.prototype.setSelectedClass = function(el){
    el.oldcomonentclass= el.oldcomonentclass ?
    el.getAttribute('class') : null;
    el.setAttribute('class', (el.oldcomonentclass) ? 
        el.oldcomonentclass + " redactor_selected" : "redactor_selected");
}

redactor.prototype.resetSelectedClass = function(el){
    if (el.oldcomonentclass)
        el.setAttribute('class',el.oldcomonentclass);
}
 
    
// обработчики событий   
 
/* empty*/
redactor.prototype.onmos = function (){
    event.preventDefault();
    event.stopPropagation();
} 

redactor.prototype.onmosnopropogate = function (){
    event.preventDefault();
} 

redactor.prototype.click_component = function(){
    var el= this.getTarget(event);
    mainlibutil.designtime.setCurrentRedactor(window);
    this.select_component(el, event.shiftKey, event.ctrlKey);
    event.stopPropagation();
}

redactor.prototype.click_parented = function(ev){
if (ev && ev.clientX.toString() && ev.clientY.toString())
       this.createLibComponent(ev.clientX.toString(), ev.clientY.toString());
}

redactor.prototype.createLibComponent = function(x, y){
    var created = mainlibutil.designtime.getSelectedComponent();
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
redactor.prototype.select_component = function(el, shift, ctnrl){
    if (this.selectedElemens==null){
        this.selectedElemens = new Array();
    }
    
    var el_class = el.getAttribute('class');
    if (el_class=="redactor_selected"){
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
redactor.prototype.keybord_dispatcher = function (){
    
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

redactor.prototype.moveElements = function (event){
    
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



redactor.prototype.mousemove_document = function (){
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


redactor.prototype.mousedown_document = function (){
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




redactor.prototype.mousedown_component = function (){
    if ((event.button==0)){
        var trgt = this.getTarget(event)
        var cls = trgt.getAttribute('class');
        if ((cls) && (cls.search('redactor_selected')!=-1)){
            this.draggedstart=true;
            this.objins_draggedstart=undefined;
            return;
        }
    }
    this.draggedstart=undefined;
}


redactor.prototype.mouseup_document = function (){
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

redactor.prototype.contextmenue = function (){
    this.createContextMenu(event);
    event.stopPropagation();
    event.preventDefault();    
}



redactor.prototype.createWindow = function(id, top, left, width, height){
   
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
            
        var result = mainlibutil.www.create_window(this.instantdocument, id, top, left, height, width, style);
        return result;
    }
    return undefined;
}

// контекстное меню

redactor.prototype.createContextMenu = function(){


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
        
   mainlibutil.html.create_style(this.contextmenu.bindelement,styletxt); 
   
   var table = mainlibutil.html.create_table(this.contextmenu.bindelement, null, 'scrollable');
   table.setAttribute('width' , '100%');
           
   var tbody= mainlibutil.html.create_tbody(table);

       
   this.ContextMenuComponent(tbody);
    
   this.contextmenu.onmouseout=function(){
        if (event.fromElement==this) {
            document.red.ContextMenuDestroy();
        }
    }
}

redactor.prototype.ContextMenuButton = function(tbody, name, enable, func){
    
    var btn = mainlibutil.html.create_button( 
        mainlibutil.html.create_td(
            mainlibutil.html.create_tr(tbody)), null , null, name, func);

}




redactor.prototype.ContextMenuComponent = function(tbody){
    
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



redactor.prototype.ContextMenuDestroy = function(){
    
    if (this.contextmenu){
        this.contextmenu.parentNode.removeChild(this.contextmenu);
    }
    this.contextmenu=undefined;

}

// Инспектор объектов


redactor.prototype.show_property = function(){
    
    
    var attriblist=this.getAttributeList();


    this.inspectorFrame=mainlibutil.designtime.getObjectInspector();
    if (!this.inspectorFrame) return;
    this.inspectortbody=mainlibutil.designtime.getObjectInspectorTbody();
    
    mainlibutil.dom.clearChildNode(this.inspectortbody);   

    var trh= mainlibutil.html.create_tr(this.inspectortbody);

            
    var th1= mainlibutil.html.create_th(trh);
    //th1.setAttribute('width','50%');
    th1.innerHTML='Attribute';
            
    var th2= mainlibutil.html.create_th(trh);
    th2.setAttribute('width','80%');
    th2.innerHTML='Value';

                            
    for (var i=0; i<attriblist.length; ++i ){
        
        var tr= mainlibutil.html.create_tr(this.inspectortbody);
       
        var td1= mainlibutil.html.create_td(tr);
        td1.innerHTML=attriblist[i]['name'];
        
        td1.className='static';
   
        var td2= mainlibutil.html.create_td(tr, 'margin: 0 0 0 0; padding: 0 0 0 0; ');
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

redactor.prototype.attribute_editor = function(el){
    if (!this.inspectorFrame){
        this.show_property(el);
    }


}

redactor.prototype.property_row_focus = function(event){
    
    if (event.target.tagname="td"){
        var td= event.target;
        var value=event.target.innerHTML;
        
        var type = td['type'] ? td['type']  : 0;
        
        if (type<=2 && event.button>0){           
            var retval = mainlibutil.designtime.propertydialog(td['name'], value);
            if (retval) 
                this.setProperty(td.prop_dvn,retval);
            event.preventDefault();
            event.stopPropagation();
            return;
        }
        
        switch (type){
            
            case 0:
            case 1:{
                mainlibutil.dom.clearChildNode(td);
                mainlibutil.html.create_input(td, 'text', value);
                break;
            }
            case 2:
            case 3:{
              
                var list=td['list'];
                mainlibutil.dom.clearChildNode(td);        
                mainlibutil.html.create_select(td,'text',value,list,type==3)       
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


redactor.prototype.property_event = function(el){
    
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


redactor.prototype.property_leave_focus = function(event){
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


redactor.prototype.setNeedSave = function(){
    this.needsave=true; 
    mainlibutil.designtime.setMainWindowToolStatus(1);
}



    






            
                
                
                
                
                
                
                
                
  
        
                        
