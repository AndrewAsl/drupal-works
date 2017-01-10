<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function rastvor_set_link(){
    $output = '';
    $output .=  '<div id="btn-group"><h3>Вид раствора</h3>';
    $output .=  '<button disabled value="1">цементный кладочный</button>'
            . '<button value="2">цементный отделочный</button>'
            . '<button value="3">цементно-известковый кладочный</button>'
            . '<button value="4">цементно-известковый отделочный</button>'
            . '<button value="5">известковый отделочный</button>';
    $output .=  '</div>';
    $output .= render(drupal_get_form('rastvor_form'));
    $output .= render(drupal_get_form('rastvor_act_form'));
    return $output;
}
function rastvor_form($form, &$form_state){
    $form = array();
    
    $form['rastvor'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );    
    
    $form['rastvor']['rastvornames'] = array(
        '#title' => t('Марка раствора'),
        '#type' => 'select',
        '#options' => rastvor_get_options('rastvortype'),
        '#default_value' => 2,
        //'#size' => 10,
        '#description' => t('Выберите марку раствора'),
        '#prefix' => '<div id="ajaxoptions"',
    );
    $form['rastvor']['cementnames'] = array(
        '#title' => t('Марка цемента'),
        '#type' => 'select',
        '#options' => __cement_get_options('rastvorcementname'),
        '#default_value' => 2,
        '#description' => t('Выберите марку цемента'),
    );
    $form['rastvor']['volume'] = array(
        '#title' => t('Количество раствора'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите объём, м3'),
        '#element_validate' => array('element_validate_number'),
        '#suffix' => '</div>',
    );
    
    $form['result'] = array(
        '#title' => t('Результат расчетов'),
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="results"><h3>Результат расчетов</h3>',
        '#suffix' =>'</div>'  
    );
    
    $form['result']['cement'] = array(
       '#title' => t('Цемент'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="cement"></div>',
       //'#suffix' =>'</div>'
    );
    $form['result']['pesok'] = array(
       '#title' => t('Песок'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="pesok"></div>',
       //'#suffix' =>'</div>'
    );
    $form['result']['izvest'] = array(
       '#title' => t('Известь строительная'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="izvest"></div>',
       //'#suffix' =>'</div>'
    );
    $form['result']['voda'] = array(
       '#title' => t('Вода'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="voda"></div>',
       //'#suffix' =>'</div>'
    );
    
    
    $form['result']['actbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в Акт переработки материалов'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'rastvor') . '/rastvorcalcul.js',
    );

    return $form;
}


function rastvor_act_form($form, &$form_state){
    $form['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-12"><h3>Акт переработки материалов</h3></div>'
        .'<div><table id="spec" class="table-bordered"><tbody>'
        . '<tr>'
        . '<th rowspan="3">№ п/п</th>'
        . '<th rowspan="3">Наименование изготавливаемого материала</th>'
        . '<th rowspan="3">Единица измерения</th>'
        . '<th rowspan="3">Количество</th>'
        . '<th rowspan="3">Марка цемента</th>'
        . '<th colspan="8">Наименование исходных материалов</th>'
        . '</tr>'
        . '<tr>'
        . '<th colspan="2">Цемент <span id="cementnames"></span>, т</th>'
        . '<th colspan="2">Песок 1 класса, м<sup>3</sup></th>'
        . '<th colspan="2">Известь строительная, т</th>'
        . '<th colspan="2">Вода, м<sup>3</sup></th>'
        .'</tr>'
        .'<tr>'
        . '<th>норма расхода на единицу измерения</th>'
        . '<th>всего на объем</th>'
        . '<th>норма расхода на единицу измерения</th>'
        . '<th>всего на объем</th>'
        . '<th>норма расхода на единицу измерения</th>'
        . '<th>всего на объем</th>'
        . '<th>норма расхода на единицу измерения</th>'
        . '<th>всего на объем</th>'        
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    return $form;
}

function rastvor_get_options ($basename = '', $select = ''){
    $select = ($select)? $select : 1 ;    
    $entries = db_select($basename);
            //-> fields($basename);
            //-> execute()
            //-> fetchAll();
    //dsm($entries);
    switch ($basename) {
        case 'rastvortype':
            $entries ->join('rastvorcatunion', 'rcu', 'rcu.rastvorid = '.$basename.'.rastvorid  AND rcu.rastvorcatid = '.$select );
            //dsm ($entries);
            $entries -> fields($basename, array('rastvorid', 'title'));
            $unionentries = $entries -> execute() -> fetchAll();
            foreach ($unionentries as $entry){
                //dsm($entry);
                $options[$entry->rastvorid] = $entry->title;
            }            
            break;
             
        default:
            break;
    }
    return $options;
}

function __cement_get_options($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'rastvorcementname':
                $options[$entry->cementid] = $entry->title;
                break;
            default:
                break;
        }
    }
    return $options;
}

function rastvor_calculate(){
    $rastvorcatid = $_POST['rastvorcatid'];
    $rastvorid = $_POST['rastvorid'];
    $cementid = $_POST['cementid'];
    $infos = db_select('rastvordataset', 'rdata')
        ->fields('rdata', array('cement', 'pesok', 'izvest', 'voda',))
        ->condition('rdata.rastvorcatid', $rastvorcatid)
        ->condition('rdata.rastvorid', $rastvorid)
        ->condition('rdata.cementid', $cementid)
        ->execute()
        ->fetchAll();
    $cement = $infos[0]->cement;
    $pesok = $infos[0]->pesok;
    $izvest = $infos[0]->izvest;
    $voda = $infos[0]->voda;
    drupal_json_output(array(                       
                'cement'=> $cement,                       
                'pesok'=> $pesok,                       
                'izvest'=> $izvest,                       
                'voda'=> $voda,                      
                ));       
    drupal_exit();
}

function rastvor_ajax_get_options(){
    //$txt = 'some';
    $basename = ($_POST['basename'])? $_POST['basename'] : $basename;
    $select = ($_POST['ajaxoptions'])? $_POST['ajaxoptions'] : 1 ;
    $options = rastvor_get_options($basename, $select);
    //dsm($options);
    drupal_json_output(array('options'=>$options, 'btn'=>$select));
    drupal_exit();
}