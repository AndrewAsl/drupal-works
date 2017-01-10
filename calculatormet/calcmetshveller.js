/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetSteel = {
        'attach': function(context, settings) {
            
            var csa = 0.2280;;
            
            var PreventEnter = function(){    
                $('input#edit-shveller-length').keypress( function(e){
                    if (e.keyCode === 13){                        
                            var mass = $(this).val() * $('span#massonem').text();
                            var csadraw = $(this).val() * csa;
                            $('div#masscalcul').text(mass);
                            $('div#csadraw').text(csadraw);
                            e.preventDefault();
                        }                        
                    }
                );
            };
            
            var CalculateAndPlace = function (){
                $('input#edit-shveller-length').change(function(){
                        var mass = $(this).val() * $('span#massonem').text();
                        var csadraw = $(this).val() * csa;
                        $('div#masscalcul').text(mass);
                        $('div#csadraw').text(csadraw);
                    });
            };
            
            var GetInfo = function(basename, value){
                //csa = SetCsa();
                value.each(function(){
                  $.post('/services/calcmet/shveller/shveller_change_info', 
                  {'shvellername': basename, 'option': value.val()}, 
                  function(data){
                        $('span#height').text(data.height);
                        $('span#width').text(data.polkaw);
                        $('span#thickness').text(data.thick);
                        $('span#thickpolka').text(data.polkathick);
                        $('span#massonem').text(data.massonem);
                        $('span#csa').text(data.csatext);
                        csa = data.csa;                        
                        if($('input#edit-shveller-length').val()){
                          var mass = $('input#edit-shveller-length').val() * data.massonem;  
                          var csadraw = $('input#edit-shveller-length').val() * csa;  
                          $('div#masscalcul').text(mass);
                          $('div#csadraw').text(csadraw);
                        } else {
                           $('div#masscalcul').text(''); 
                           $('div#csadraw').text(''); 
                        }                      
                  });
              });
            };
            
            var ChangeOptions = function(){
                var name = $('select[id^="edit-shveller"]');
                name.on('change', function(){
                    if (name[0].id === 'edit-shveller-shvellernames'){
                        GetInfo('shvell1', $('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();                        
                    } else if (name[0].id === 'edit-shveller-shvellernames2'){
                        GetInfo('shvell2',$('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();                       
                    }                    
                    else {
                        return;
                    }
                });
            };
            
            var AddToSpec = function(){
                var btntospec = $('#btnspec button');
                btntospec.on('click', function(e){
                    e.preventDefault();
                    //alert ('click');
                    var cat = $('select#edit-cat option:selected').text();
                    var numpp = $('table#spec tr').length;
                    var title, dlinaintbl, massintbl, csadraw, html;
                        title = 'Швеллер ' + cat.toLowerCase()+' '+ $('select[id^=edit-shveller] option:selected').text();
                        dlinaintbl = $('#edit-shveller-length').val();
                        massintbl = $('#masscalcul').text();
                        csadraw = $('#csadraw').text();
                        if (title && dlinaintbl && massintbl){
                            html = '<tr><td>'+ numpp +'</td>'
                                +'<td>' + title + '</td>' 
                                +'<td>'+ dlinaintbl + '</td>' 
                                +'<td>'+massintbl+'</td>'
                                +'<td>'+csadraw+'</td>'
                                +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
                            $('table#spec').append(html);
                        } else {
                            alert ('Необходимо заполнить все данные');
                            return false;
                        }                                           
                    var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>';
                       if(!$('div#btncab').length) 
                        $('#edit-spec').append(btn);
                    //console.log(html);
                    var delrow = $("table#spec .deleterow", context);
                    delrow.on("click",function(e) {
                        e.preventDefault();
                        var tr = $(this).closest('tr');
                        tr.fadeOut(400, function(){
                            tr.remove();
                            if ($('table#spec tr').length === 1){
                                $('div#btncab').remove();
                            }
                        });
                      return false;
                    });
                    $('div#btncab button').one("click",function(e) {
                       //e.preventDefault();
                       alert ('Данные в личный кабинет отправлены' );
                       return false;
                    });
                });
            };
            
            $('select#edit-cat', context).on('change', function(e){
                e.stopPropagation();
                var txtForCsa = $('select#edit-cat option:selected').text();
                //console.log (txtForCsa);
                switch (txtForCsa){
                    case 'У - с уклоном внутренних граней полок':
                        csa = 0.2280;
                    break;    
                    case 'П - с параллельными гранями полок':
                        csa = 0.2280;
                    break;    
                    case 'Э - экономичные с параллельными гранями полок':
                        csa = 0.2256;
                    break;    
                    case 'Л - легкой серии с параллельными гранями полок':
                        csa = 0.2164;
                    break;    
                    case 'С – специальные':
                        csa = 0.4204;
                    break;
                }
                $('select#edit-cat option:selected').each(
                    function(){  
                      $.post('/services/calcmet/shveller/shveller_change_options', {'ajaxshvellerchangeoptions': $(this).val()}, function(data){
                          $('section#block-system-main form[id^="calcmet-shveller"]').replaceWith(data);
                      })
                      .always(function(){ ChangeOptions(); CalculateAndPlace(); PreventEnter(); AddToSpec(); });  
                    }                                    
                );
                
            });     
            
            //SetCsa();
            CalculateAndPlace();
            PreventEnter();
            ChangeOptions();
            AddToSpec();
        }       
  };         
})(jQuery);

