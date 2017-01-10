<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
    Раздел по квадрату
 */
function calcmet_kvadrat_form($form, &$form_state){
    $form = array();
    $form['kvadrat'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone"></div>',
        //'#suffix' =>'</div>'  
    );
    
    $form['kvadrat']['options'] = array(
        '#title' => t('Сторона квадрата'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetkvadrat'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип квадрата'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'kvadrat_change_info',
        ),*/
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['kvadrat']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'kvadrat_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['kvadrat']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['kvadrat']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['kvadrat']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/kvadrat.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['kvadrat']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="kvadrat-info">'
        . '<strong>Площадь сечения, см2</strong> <span id="csa">0.36</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.283</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 2591-2006 "Прокат сортовой стальной горячекатаный квадратный. '
        . 'Сортамент" утвержден постановлением Госстандарта Республики Беларусь от 30.01.2007 № 4',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['kvadrat']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Сторона</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, кг</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetkvadrat.js',
    );
    return $form;
}
/*
 * Конец формы для двутавра
 */

function kvadrat_change_info(){
    $select = $_POST['kvadratselect'];
    //dsm($select);
    $infos = db_select('calcmetkvadrat', 'kv')
            ->fields('kv', array('kvcsa', 'kvmassonem',))
            ->condition('kv.kvdid', $select)
            ->execute()
            ->fetchAll();
    $csa = $infos[0]->kvcsa;
    $massonem = $infos[0]->kvmassonem;
    drupal_json_output(array(
                        'csa' => $csa, 
                        'massonem'=>$massonem,
                        
        ));
    drupal_exit();
}

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetkvadrat':
                $options[$entry->kvdid] = $entry->storona;
                break;

            default:
                break;
        }
    }
    return $options;
}