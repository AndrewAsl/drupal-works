/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function($) {
    Drupal.behaviors.calcRastvor = {
        'attach': function(context, settings) {
            
            var valbtn=1;
            var normcement = 0.136;
            var normpesok = 1.25;
            var normvoda = 0.35;
            var normizvest = 0;
            
            if (valbtn == 1)
                $('div[id*="result-izvest"]').hide();
            
            $('div#btn-group button').click(function(){
                $('#cement').text('');
                $('#pesok').text('');
                $('#izvest').text('');
                $('#voda').text('');
            });
            
            $('input[id*="volume"]').change(function(){
                getDataAndCalculate();
            });
            
            $('select[id*="cementnames"]').change(function(){
                 if($('input[id*="volume"]').val())
                    getDataAndCalculate();
            });
            
            $('select[id*="rastvornames"]').change(function(){
                if($('input[id*="volume"]').val())
                    getDataAndCalculate();
            });
            
            $('input[id*="volume"]').keypress(function(e){
                if(e.keyCode == 13){
                    e.preventDefault();
                    getDataAndCalculate();
                }
            });
            
            var getDataAndCalculate = function(){
                var rastvorcatid = valbtn;
                var cementid;
                if( rastvorcatid == 5)
                    cementid = 0;
                else
                    cementid = $('select[id*="cementnames"] option:selected').val();
                var rastvorid = $('select[id*="rastvornames"] option:selected').val();
                
                var volume = parseFloat($('input[id*="volume"]').val());
                $.post('/services/rastvor/calculate',
                       {rastvorcatid:rastvorcatid, rastvorid:rastvorid, cementid:cementid}, 
                    function(data){
                        if (data.izvest == 0){
                            $('div[id*="result-izvest"]').hide();
                            $('div[id*="result-cement"]').show();
                        }
                        if (data.cement == 0){
                            $('div[id*="result-cement"]').hide();
                            $('div[id*="result-izvest"]').show();
                        }
                        if (isNaN(volume)){
                            alert('Введите число');
                            return false;
                        }
                        else{
                            var cement = volume*data.cement;
                            var pesok = volume*data.pesok;
                            var izvest = volume*data.izvest;
                            var voda = volume*data.voda;
                            $('#cement').text(cement);
                            $('#pesok').text(pesok);
                            $('#izvest').text(izvest);
                            $('#voda').text(voda);
                        }         
                       
                    }
                )
                .done(function(data){
                    normcement = data.cement;
                    normpesok = data.pesok;
                    normvoda = data.voda;
                    normizvest = data.izvest;
                });
            };            
            
            $('div#btn-group button').each(
                function(){
                    $(this).click( function(){                          
                        $(this).siblings().removeAttr('disabled');
                        $(this).attr('disabled', 'disabled');                      

                        $('select[id*="rastvornames"] option').remove();

                        $.post('/services/rastvor/getoptions', {'basename': 'rastvortype','ajaxoptions': $(this).val()}, function(data){
                            //console.log(data);
                            $.each(data.options, function(key, value){
                                $('select[id*="rastvornames"]')
                                    .append($("<option></option>")
                                    .attr("value",key)
                                    .text(value));
                            $('select[id*="rastvornames"] option').first().attr('selected', 'selected');
                                //console.log (key + ':' + value);
                            });
                        }).done(function(data){
                            $('#cement').empty();
                            $('#pesok').empty();
                            $('#izvest').empty();
                            $('#voda').empty();
                            $('input[id*="rastvor-volume"]').val('');
                            if (data.btn == 1 || data.btn == 2){
                                $('div[id*="result-izvest"]').hide();
                                $('div[id*="result-cement"]').show();
                                $('div[class*="cementnames"]').show();
                            }
                            else if (data.btn == 5){
                                $('div[id*="result-cement"]').hide();
                                $('div[id*="result-izvest"]').show();
                                $('div[class*="cementnames"]').hide();
                            }
                            else {
                                $('div[id*="result-cement"]').show();
                                $('div[id*="result-izvest"]').show();
                                $('div[class*="cementnames"]').show();
                            }
                                valbtn = parseInt(data.btn);
                            });

                    });  
                }                                    
            );
            var btntospec = $('button[id*="actbutton"]');
            btntospec.on('click', function(e){
                e.preventDefault();
                var name;
                $('#btn-group button').each(function(){
                    if ($(this).attr('disabled'))
                        name = $(this).text();
                
                });
                var rastvormark = $('select[id*="rastvornames"] option:selected').text();
                if (rastvormark.indexOf(":") != -1)
                    rastvormark = 'состава ' + rastvormark;
                var numpp = $('table#spec tr').length - 2;
                var cementmark;
                if (name == 'известковый отделочный')
                    cementmark = '-';
                else 
                    cementmark = $('select[id*="cementnames"] option:selected').text();
                var volumerastvor = $('input[id*="volume"]').val();
                var cement = parseFloat($('#cement').text());
                var pesok = parseFloat($('#pesok').text());
                var izvest = parseFloat($('#izvest').text());
                var voda = parseFloat($('#voda').text());
                var html = '<tr>\n\
                            <td>'+ numpp +'</td>'
                            +'<td> Раствор '+ name + ' ' + rastvormark + '</td>' 
                            +'<td>м<sup>3</sup></td>' 
                            +'<td>'+volumerastvor+'</td>'
                            +'<td>'+cementmark+'</td>'
                            +'<td>'+normcement+'</td>'
                            +'<td>'+cement.toFixed(3)+'</td>'
                            +'<td>'+normpesok+'</td>'
                            +'<td>'+pesok.toFixed(3)+'</td>'
                            +'<td>'+normizvest+'</td>'
                            +'<td>'+izvest.toFixed(3)+'</td>'
                            +'<td>'+normvoda+'</td>'
                            +'<td>'+voda.toFixed(3)+'</td>'
                            +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
                if(cement || izvest)
                    $('table#spec').append(html);
                else
                    alert('Не заполнены данные');
                var delrow = $("table#spec .deleterow", context);
                delrow.on("click",function(e) {
                    e.preventDefault();
                    var tr = $(this).closest('tr');
                    tr.fadeOut(400, function(){
                        tr.remove();
                        if ($('table#spec tr').length -2 === 1){
                            $('div#btncab').remove();
                        }
                    });
                  return false;
                });
                var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> \n\
                           <button class="btn btn-success" type="submit">Добавить в личный кабинет</button>\n\
                           <button class="btn btn-success" type="submit">Сохранить в виде "Акта формы С-7"</button>\n\
                           </div>';
                if(!$('div#btncab').length) 
                   $('#edit-spec').append(btn);
                $('div#btncab button').one("click",function(e) {
                   //e.preventDefault();
                   alert ('Данные отправлены' );
                   return false;
                });   
            });    
        }
    };
})(jQuery);
        
