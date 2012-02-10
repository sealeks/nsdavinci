
function init_project_controller(){
    chrome.controller = new project_controller(document);
    chrome.controller.attach();
}


////

function project_controller(doc){
    this.document=doc;} 


project_controller.prototype.attach = function(){
    if (!this.formlist){
        this.formlist = mainlibutil.global.getFormList();
        this.init_form();
    }
}


project_controller.prototype.init_form = function(){
    if (this.document){
        var elp=this.document.getElementsByTagName('project');
        if (elp && elp.length>0)
            this.projectElement=elp[0];
        if (this.projectElement)
            this.projectPath=this.projectElement.getAttribute('path');
        
        var els=this.document.getElementsByTagName('form');
        
        for (var i=0; i<els.length;++i){
          var path = this.projectPath && els[i].getAttribute('file') ? this.projectPath.toString() + els[i].getAttribute('file').toString() : 
                     els[i].getAttribute('file') ? els[i].getAttribute('file').toString() : null; 
          if (path){   
          var win=window.open(path,
                              els[i].getAttribute('name')  ? els[i].getAttribute('name') :  '',
                              els[i].getAttribute('param') ? els[i].getAttribute('param') : '');
                
                
          window.form_list=this.formlist;
          
          this.formlist.push({'name' : els[i].getAttribute('name'),
                              'path'  : path,
                              'param'  : els[i].getAttribute('param'),
                              'window'  : win});}         
        }
        window.close();
    }
}









