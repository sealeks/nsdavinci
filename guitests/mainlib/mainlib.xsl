<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:mlib="http://dvnci/mlib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
extension-element-prefixes="mlib">
    
    <xsl:import href="mainlibstyle.xsl"/>

    <xsl:template name="mainlib">
        
        <script type="text/javascript" xlink:href="../mainlib/js/mainlibutil.js"></script>
        <script type="text/javascript" xlink:href="../mainlib/js/startup.js"></script>   
        <script type="text/javascript" xlink:href="../mainlib/js/redactor.js"></script> 
        <script type="text/javascript" xlink:href="../mainlib/js/mainlib.js"></script>

        
        <xsl:call-template name="apply_mlib_armatfilter"/>
        <xsl:call-template name="apply_mlib_style"/>
          
    </xsl:template>
    
    
    
    
    <xsl:template name="apply_mlib_schema">    
        <xsl:attribute name="xsi:schemaLocation">
            <xsl:text>../mainlib/maillib.xsd</xsl:text>
        </xsl:attribute>  
    </xsl:template>
   
     
    
    <!-- Motor template-->
    
    
    <xsl:template name="apply_mlib_motorbase">    
        <circle>
            <xsl:attribute name="cx">
                <xsl:text>500</xsl:text>
            </xsl:attribute>
            <xsl:attribute name="cy">
                <xsl:text>500</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="r">
                <xsl:text>300</xsl:text>
            </xsl:attribute> 
            <xsl:attribute name="stroke-width">
                <xsl:text>20</xsl:text>
            </xsl:attribute> 
        </circle>
        <path>
            <xsl:attribute name="d">
                <xsl:text>M 400 600 L 400 400 L 500 500 L 600 400 L 600 600</xsl:text>
            </xsl:attribute>
            <xsl:attribute name="stroke-width">
                <xsl:text>30</xsl:text>
            </xsl:attribute> 
        </path> 
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_motorlocal">    
        <circle>
            <xsl:attribute name="cx">
                <xsl:text>150</xsl:text>
            </xsl:attribute>
            <xsl:attribute name="cy">
                <xsl:text>150</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="r">
                <xsl:text>80</xsl:text>
            </xsl:attribute> 
        </circle>
        <path>
            <xsl:attribute name="d">
                <xsl:text>M 120 180 L 120 120 L 150 150 L 180 120 L 180 180</xsl:text>
            </xsl:attribute>
        </path>
    </xsl:template>   
    
    
    
    
    
    <xsl:template match="//mlib:motor" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            
            <xsl:variable name="envir"> 
                <xsl:value-of select="@environment"/> 
            </xsl:variable>
                                              
            <xsl:attribute name="desc">
                <xsl:if test="boolean(@on)">
                    <xsl:value-of select="@on"/>
                </xsl:if>
            </xsl:attribute>
                    
            <xsl:attribute name="header">
                <xsl:if test="boolean(@header)">
                    <xsl:value-of select="@header"/>
                </xsl:if>
            </xsl:attribute>    
            
            <xsl:choose>
                <xsl:when test="boolean(@ron) and not(@ron='')">   
                    <xsl:attribute name="onmouseover">
                        <xsl:text>main_motor_click(this,'</xsl:text> 
                        <xsl:value-of select="@header"/>
                        <xsl:text>','</xsl:text>
                        <xsl:value-of select="@ron"/>
                        <xsl:text>');</xsl:text>
                    </xsl:attribute>
                    <xsl:choose>
                        <xsl:when test="boolean(@local) and not(@local='')">
                            <xsl:attribute name="cursor">
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>.valid) ? ((</xsl:text>
                                <xsl:value-of select="@local"/>
                                <xsl:text>) ? 'default' : 'pointer') : 'default'}</xsl:text>
                            </xsl:attribute> 
                        </xsl:when> 
                        <xsl:when test="boolean(@on) and not(@on='')">
                            <xsl:attribute name="cursor">
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>.valid) ?'pointer' : 'default'}</xsl:text>
                            </xsl:attribute>    
                        </xsl:when>     
                        <xsl:otherwise> 
                            <xsl:attribute name="cursor">
                                <xsl:text>default</xsl:text>
                            </xsl:attribute>
                        </xsl:otherwise>                           
                    </xsl:choose>        
                </xsl:when>
                
            </xsl:choose>

            
            <svg>  
                
                <xsl:call-template name="apply_rect"/>
                
                <xsl:attribute name="viewBox">
                    <xsl:text>0 0 1000 1000</xsl:text>
                </xsl:attribute>
                <xsl:attribute name="preserveAspectRatio">
                    <xsl:text>none</xsl:text>
                </xsl:attribute>

                <g>
                    <xsl:choose>
                        <xsl:when test="boolean(@on) and not(@on='')">   
                            <xsl:attribute name="filter">
                                <xsl:text>url(#armat_filter1)</xsl:text>
                            </xsl:attribute> 
                            <xsl:attribute name="class">
                                <xsl:text>#{ (!</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>.valid)  ? 'non'  : ((</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>)  ? 'on</xsl:text>
                                <xsl:value-of select="$envir"/>
                                <xsl:text>':  'off</xsl:text>
                                <xsl:value-of select="$envir"/>
                                <xsl:text>')}</xsl:text>
                            </xsl:attribute>

                            <xsl:call-template name="apply_mlib_motorbase"/>
                            
                                                    
                        </xsl:when>
                        <xsl:otherwise>

                            <xsl:attribute name="class">
                                <xsl:text>non</xsl:text>
                            </xsl:attribute> 
                            <xsl:attribute name="filter">
                                <xsl:text>#armat_filter1</xsl:text>
                            </xsl:attribute> 
                            
                            <xsl:call-template name="apply_mlib_motorbase"/>
                            
                        </xsl:otherwise>
                    </xsl:choose>
                    
                </g>
                
   
                <xsl:choose>
                    <xsl:when test="boolean(@local) and not(@local='')">
                        <g stroke-width="5">
                            <xsl:attribute name="class">
                                <xsl:text>#{ (!</xsl:text>
                                <xsl:value-of select="@local"/>
                                <xsl:text>.valid) ?  'transparent' : ((</xsl:text> 
                                <xsl:value-of select="@local"/>
                                <xsl:text>) ? 'local'  : 'transparent') }</xsl:text>
                            </xsl:attribute>
                            
                            <xsl:call-template name="apply_mlib_motorlocal"/>

                        </g>    
                       
                    </xsl:when>
                </xsl:choose>
                                                 

                <xsl:choose>                
                    <xsl:when test="(boolean(@alarm) and not(@alarm=''))">
                        <g  class="alarm" filter="#armat_filter1" opacity="0.3">              
                            <xsl:attribute name="display">
                                <xsl:text>#{ min(</xsl:text>
                                <xsl:value-of select="@alarm"/>
                                <xsl:text> , </xsl:text>
                                <xsl:value-of select="@alarm"/>
                                <xsl:text>.valid </xsl:text>
                                <xsl:text>)   ? 'block'  : </xsl:text>
                                <xsl:choose>                
                                    <xsl:when test="(boolean(@alarmack) and not(@alarmack=''))">
                                        <xsl:text> ((min(</xsl:text>
                                        <xsl:value-of select="@alarmack"/>
                                        <xsl:text> , </xsl:text>
                                        <xsl:value-of select="@alarmack"/>
                                        <xsl:text>.valid))   ? 'block'  : 'none')  }</xsl:text>
                                    </xsl:when>   
                                    <xsl:otherwise>
                                        <xsl:text>    'none'  } </xsl:text>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </xsl:attribute>                            
                            <circle cx="500" cy="500" r="320"/>
                            <animate id="a2" attributeType="XML" attributeName="opacity" from="0.3" to="0.9" dur="1000ms" calcMode = "linear" repeatCount="indefinite">
                                <xsl:choose>                
                                    <xsl:when test="(boolean(@alarmack) and not(@alarmack=''))">
                                        <xsl:attribute name="to">
                                            <xsl:text>#{ (</xsl:text>
                                            <xsl:value-of select="@alarmack"/>
                                            <xsl:text>)   ? '0.3'  : '0.9' }</xsl:text>
                                        </xsl:attribute> 
                                    </xsl:when>
                                </xsl:choose>
                            </animate>    
                        </g>     
                    </xsl:when>   
                </xsl:choose>
                
                

            </svg>       
        </g>  
    </xsl:template>
    
    
    
    <xsl:template match="//mlib:button" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            
            

                                              

            
            <!--xsl:attribute name="filter">
                                <xsl:text>url(#armat_filter1)</xsl:text>
            </xsl:attribute--> 


            <rect role="button"  aria-pressed="true" class="disablebuttongrad">
                <xsl:attribute name="onmouseover">
                    <xsl:text>if (event.toElement==this) {this.setAttribute('style','stroke-width : 1; stroke : red;')};</xsl:text>
                </xsl:attribute>
                <xsl:attribute name="onmouseout">
                    <xsl:text>if (event.fromElement==this) {this.setAttribute('style','stroke-width : 0; stroke : trasparent;')};</xsl:text>
                </xsl:attribute>  
                <xsl:choose>                
                    <xsl:when test="(boolean(@param) and not(@param=''))">  
                        <xsl:attribute name="onclick">                   
                            <xsl:text>dvnci_exec('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text>
                        </xsl:attribute> 
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:choose>                
                            <xsl:when test="(boolean(@click) and not(@click=''))">      
                                <xsl:attribute name="onclick">
                                    <xsl:value-of select="@click"/>
                                </xsl:attribute>
                            </xsl:when>
                        </xsl:choose>
                    </xsl:otherwise>    
                </xsl:choose> 
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_r"/>

            </rect> 
            
            <svg>                
                <xsl:call-template name="apply_rect"/>
                <text class="central_svgnatext">
                    <xsl:attribute name="x">
                        <xsl:value-of select="@width div 2"/>
                    </xsl:attribute>
                    <xsl:attribute name="y">
                        <xsl:value-of select="@height div 2"/>
                    </xsl:attribute>
                    <xsl:choose>                
                        <xsl:when test="(boolean(@fontstyle) and not(@fontstyle=''))">
                            <xsl:attribute name="style">
                                <xsl:value-of select="@fontstyle"/>
                            </xsl:attribute>
                        </xsl:when>
                    </xsl:choose>     
                    <xsl:value-of select="@caption"/>
                </text>
            </svg>      
    
    
        </g>  
    </xsl:template>
    
    
    <xsl:template match="//mlib:bitbutton" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template  name="apply_visible"/>

            <rect role="button"  aria-pressed="true" class="disablebuttongrad">
                <xsl:attribute name="onmouseover">
                    <xsl:text>if (event.toElement==this) {this.setAttribute('style','stroke-width : 1; stroke : red;')};</xsl:text>
                </xsl:attribute>
                <xsl:attribute name="onmouseout">
                    <xsl:text>if (event.fromElement==this) {this.setAttribute('style','stroke-width : 0; stroke : trasparent;')};</xsl:text>
                </xsl:attribute>  
                <xsl:choose>                
                    <xsl:when test="(boolean(@param) and not(@param=''))">  
                        <xsl:attribute name="onclick">                   
                            <xsl:text>dvnci_exec('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text>
                        </xsl:attribute> 
                    </xsl:when>
                </xsl:choose> 
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_r"/>

            </rect> 
            
            <svg>                
                <xsl:call-template name="apply_rect"/>
                <text class="central_svgnatext">
                    <xsl:attribute name="x">
                        <xsl:value-of select="@width div 2"/>
                    </xsl:attribute>
                    <xsl:attribute name="y">
                        <xsl:value-of select="@height div 2"/>
                    </xsl:attribute>
                    <xsl:choose>                
                        <xsl:when test="(boolean(@fontstyle) and not(@fontstyle=''))">
                            <xsl:attribute name="style">
                                <xsl:value-of select="@fontstyle"/>
                            </xsl:attribute>
                        </xsl:when>
                    </xsl:choose>     
                    <xsl:value-of select="@caption"/>
                </text>
            </svg>       
        </g>  
    </xsl:template>    
    
    
    <!--  rect  -->
    
   
    
    
    <xsl:template match="//mlib:rect" >
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            <xsl:variable name="landsc">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">v</xsl:when> 
                    <xsl:otherwise>h</xsl:otherwise>  
                </xsl:choose>
            </xsl:variable>
  
            
            <rect>
                
                <xsl:call-template name="apply_rect"/>
                
                <xsl:choose>
                    <xsl:when test="boolean(@stroke-width)">
                        <xsl:attribute name="stroke-width">
                            <xsl:value-of select="@stroke-width"/>
                        </xsl:attribute>
                        <xsl:attribute name="stroke">
                            <xsl:value-of select="@stroke"/>
                        </xsl:attribute>    
                    </xsl:when>
                </xsl:choose> 
                
                <xsl:call-template name="apply_r"/>
                
                
                
                <!-- Fill background-->
                
                <xsl:choose>
                    <xsl:when test=" not(@background='')">  
                        <xsl:choose>
                            <xsl:when test="(@background='gaz') or (@background='water') or (@background='air') or (@background='oil') or (@background='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@background"/>
                                    <xsl:text>grad</xsl:text>
                                    <xsl:value-of select="$landsc"/>
                                </xsl:attribute>     
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@background"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                           
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>nongrad</xsl:text>
                            <xsl:value-of select="$landsc"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                

            </rect>
            
            <!-- Interactive geometry-->
            
            <rect >
                
                
                <!-- Direction-->     
                
                <xsl:choose>
                    <xsl:when test="boolean(@direction='bt') or boolean(@direction='rl')">      
                        <xsl:attribute name="transform">
                            <xsl:text>translate(</xsl:text>
                            <xsl:value-of select="@width"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@height"/>
                            <xsl:text>)</xsl:text>
                            <xsl:text> rotate(</xsl:text>
                            <xsl:text>180,</xsl:text>
                            <xsl:value-of select="@x"/>
                            <xsl:text> , </xsl:text>
                            <xsl:value-of select="@y"/>
                            <xsl:text>)</xsl:text>
                        </xsl:attribute>  
                    </xsl:when> 
                </xsl:choose>            
                
                <xsl:attribute name="x">
                    <xsl:value-of select="@x"/>
                </xsl:attribute>
                <xsl:attribute name="y">
                    <xsl:value-of select="@y"/>
                </xsl:attribute>

                
                <xsl:choose>
                    <xsl:when test="$landsc='h'">
                        <xsl:attribute name="width">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text> - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu)/</xsl:text>
                            <xsl:text>(</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.maxeu - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu) *</xsl:text>
                            <xsl:value-of select="@width"/>
                            <xsl:text>}</xsl:text>
                        </xsl:attribute>
                        <xsl:attribute name="height">
                            <xsl:value-of select="@height"/>
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="height">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text> - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu)/</xsl:text>
                            <xsl:text>(</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.maxeu - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu) *</xsl:text>
                            <xsl:value-of select="@height"/>
                            <xsl:text>}</xsl:text>
                        </xsl:attribute>
                        <xsl:attribute name="width">
                            <xsl:value-of select="@width"/>
                        </xsl:attribute>
                    </xsl:otherwise>                    
                </xsl:choose> 
                
                <!-- Direction-->
                
                <xsl:choose>
                    <xsl:when test="boolean(@stroke-width)">
                        <xsl:attribute name="stroke-width">
                            <xsl:value-of select="@stroke-width"/>
                        </xsl:attribute>
                        <xsl:attribute name="stroke">
                            <xsl:text>trasparent</xsl:text>
                        </xsl:attribute>
                    </xsl:when>
                </xsl:choose> 
                
                <xsl:call-template name="apply_r"/>
                
                <xsl:choose>
                    <xsl:when test="not(@fill='')">  
                        <xsl:choose>
                            <xsl:when test="(@fill='gaz') or (@fill='water') or (@fill='air') or (@fill='oil') or (@fill='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@fill"/>
                                    <xsl:text>grad</xsl:text>
                                    <xsl:value-of select="$landsc"/>
                                </xsl:attribute> 
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@fill"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                                     
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>nongrad</xsl:text>
                            <xsl:value-of select="$landsc"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                
                
            </rect>                
                

        

        
        </g>
    </xsl:template>
    
    
    
    <!-- -->
    
    
    <xsl:template match="//mlib:sensor" >
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            <xsl:choose>
                <xsl:when test="boolean(@param) and not(@param='')">
                    <xsl:attribute name="onclick">
                        <xsl:text>main_label_click('</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>')</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose>
            
      
            <rect>
                
                <xsl:call-template name="apply_rect"/>
                
                <xsl:choose>
                    <xsl:when test="boolean(@stroke-width)">
                        <xsl:attribute name="stroke-width">
                            <xsl:value-of select="@stroke-width"/>
                        </xsl:attribute>
                        <xsl:attribute name="stroke">
                            <xsl:value-of select="@stroke"/>
                        </xsl:attribute>    
                    </xsl:when>
                </xsl:choose> 
                
                <xsl:call-template name="apply_r"/>
                
                
                
                <!-- Fill background-->
                
                <xsl:choose>
                    <xsl:when test=" not(@background='')">  
                        <xsl:choose>
                            <xsl:when test="(@background='gaz') or (@background='water') or (@background='air') or (@background='oil') or (@background='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@background"/>
                                    <xsl:text>gradh</xsl:text>
                                </xsl:attribute>     
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@background"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                           
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>blackgradh</xsl:text>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                
 
                

            </rect>
                
            <xsl:choose>
                <xsl:when test="boolean(@param) and not(@param='')">
                    <svg>
                        <xsl:call-template name="apply_rect"/>
                        <text>
                            
                            <xsl:choose>
                                <xsl:when test="boolean(@alighn) and (@alighn='left')">               
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width * 0.1 "/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>left_svgnatext</xsl:text>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:when test="boolean(@alighn) and (@alighn='center')">               
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width div 2"/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>central_svgnatext</xsl:text>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:otherwise>   
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width * 0.9 "/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>right_svgnatext</xsl:text>
                                    </xsl:attribute>
                                </xsl:otherwise>
                            </xsl:choose>
                            
                                
                            <xsl:choose>                              
                                <xsl:when test="boolean(@fontstyle) and not(@fontstyle='')">
                                    <xsl:attribute name="style">
                                        <xsl:value-of select="@fontstyle"/>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:attribute name="style">
                                        <xsl:text>fill: white; </xsl:text>
                                        <xsl:text>fill-size:  </xsl:text>
                                        <xsl:value-of select="@height div 1.5"/>
                                        <xsl:text>;</xsl:text>
                                    </xsl:attribute>                                    
                                </xsl:otherwise>
                            </xsl:choose>
                                
                            <xsl:choose>                              
                                <xsl:when test="boolean(@format) and not(@format='')">
                                    <xsl:text>#{ format(</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text> , '</xsl:text>
                                    <xsl:value-of select="@format"/>
                                    <xsl:text>')}</xsl:text>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:text>#{ format(</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text> , '%8.1f')}</xsl:text>                                       
                                </xsl:otherwise>
                            </xsl:choose>
                            

                            
                        </text>
                    </svg>
                </xsl:when>
            </xsl:choose>                   
            
            <!-- Interactive geometry-->
 
 


        
        </g>
    </xsl:template>



</xsl:stylesheet>
